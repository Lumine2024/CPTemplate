#!/usr/bin/env python3
"""expand.py - Expand local #include directives in C++ files.

Usage:
    python expand.py <input_file> [-o <output_file>] [-I <include_dir>]

This script recursively expands all #include "..." (local/quoted includes)
by inlining the referenced file content, while leaving #include <...>
(system includes) unchanged. Each local file is included at most once,
respecting #pragma once semantics.

Include resolution order:
  1. Relative to the directory of the file containing the #include directive.
  2. Each directory listed via -I (or the default include/ directory next to
     this script) is searched in order.

Example:
    python expand.py usage/geo/rotcal.h -o contest/D.cpp
    python expand.py usage/ds/seg.h -I /path/to/include
"""

import argparse
import os
import re
import sys

# Default include directory: the 'include/' folder next to this script.
_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
_DEFAULT_INCLUDE_DIRS = [os.path.join(_SCRIPT_DIR, "include")]


def expand(filepath: str, included: set, include_dirs: list) -> str:
    """Recursively expand local includes in a file.

    Args:
        filepath: Path to the C++ source file to expand.
        included: Set of absolute paths already included (for #pragma once).
        include_dirs: Ordered list of directories to search when a quoted
            include cannot be resolved relative to the current file.

    Returns:
        The expanded file content as a string.
    """
    abs_path = os.path.abspath(filepath)
    if abs_path in included:
        return ""
    included.add(abs_path)

    file_dir = os.path.dirname(abs_path)
    result = []

    try:
        with open(filepath, "r") as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"Error: file not found: {filepath}", file=sys.stderr)
        sys.exit(1)

    for line in lines:
        # Skip #pragma once — we handle deduplication ourselves
        if re.match(r"\s*#pragma\s+once\s*$", line):
            continue

        # Match local (quoted) include: #include "path"
        m = re.match(r'\s*#include\s+"([^"]+)"', line)
        if m:
            include_path = m.group(1)

            # 1. Try relative to the current file's directory.
            full_include = os.path.normpath(os.path.join(file_dir, include_path))

            # 2. If not found, search the configured include directories.
            if not os.path.isfile(full_include):
                for inc_dir in include_dirs:
                    candidate = os.path.normpath(os.path.join(inc_dir, include_path))
                    if os.path.isfile(candidate):
                        full_include = candidate
                        break

            expanded = expand(full_include, included, include_dirs)
            if expanded:
                result.append(expanded)
            # (if already included, we simply skip)
        else:
            result.append(line)

    return "".join(result)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Expand local #include directives in C++ files for contest submission."
    )
    parser.add_argument("input", help="Input C++ source file")
    parser.add_argument(
        "-o",
        "--output",
        help="Output file path (default: print to stdout)",
        default=None,
    )
    parser.add_argument(
        "-I",
        "--include-dir",
        action="append",
        dest="include_dirs",
        metavar="DIR",
        help=(
            "Add DIR to the include search path (can be specified multiple times). "
            "Defaults to the 'include/' directory next to this script"
            + (f": {_DEFAULT_INCLUDE_DIRS[0]}" if _DEFAULT_INCLUDE_DIRS else ".")
        ),
        default=None,
    )
    args = parser.parse_args()

    if not os.path.isfile(args.input):
        print(f"Error: '{args.input}' is not a file or does not exist.", file=sys.stderr)
        sys.exit(1)

    include_dirs = args.include_dirs if args.include_dirs is not None else _DEFAULT_INCLUDE_DIRS

    included: set = set()
    result = expand(args.input, included, include_dirs)

    if args.output:
        out_dir = os.path.dirname(os.path.abspath(args.output))
        os.makedirs(out_dir, exist_ok=True)
        with open(args.output, "w") as f:
            f.write(result)
        print(f"Expanded output written to: {args.output}")
    else:
        sys.stdout.write(result)


if __name__ == "__main__":
    main()
