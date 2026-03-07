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

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

# Default include directory: the 'include/' folder next to this script.
_SCRIPT_DIR = Path(__file__).resolve().parent
_DEFAULT_INCLUDE_DIRS = [_SCRIPT_DIR / "include", _SCRIPT_DIR]

def expand(filepath: Path, included: set[Path], include_dirs: list[Path]) -> str:
    """Recursively expand local includes in a file.

    Args:
        filepath: Path to the C++ source file to expand.
        included: Set of absolute paths already included (for #pragma once).
        include_dirs: Ordered list of directories to search when a quoted
            include cannot be resolved relative to the current file.

    Returns:
        The expanded file content as a string.
    """
    abs_path = filepath.resolve()
    if abs_path in included:
        return ""
    included.add(abs_path)

    file_dir = abs_path.parent
    result = []

    try:
        with abs_path.open("r", encoding="utf-8") as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"Error: file not found: {abs_path}", file=sys.stderr)
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
            full_include = (file_dir / include_path).resolve()

            # 2. If not found, search the configured include directories.
            if not full_include.is_file():
                for inc_dir in include_dirs:
                    candidate = (inc_dir / include_path).resolve()
                    if candidate.is_file():
                        full_include = candidate
                        break

            expanded = expand(full_include, included, include_dirs)
            if expanded:
                result.append(expanded)
            # (if already included, we simply skip)
        else:
            result.append(line)

    return "".join(result)


def main():
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
            + "Defaults to: "
            + ", ".join(str(p) for p in _DEFAULT_INCLUDE_DIRS)
        ),
        default=None,
    )
    args = parser.parse_args()

    input_path = Path(args.input).resolve()
    if not input_path.is_file():
        print(f"Error: '{args.input}' is not a file or does not exist.", file=sys.stderr)
        sys.exit(1)

    include_dirs = ([Path(p).resolve() for p in args.include_dirs] if args.include_dirs is not None else [])
    include_dirs.extend(_DEFAULT_INCLUDE_DIRS)

    included: set[Path] = set()
    result = expand(input_path, included, include_dirs)

    if args.output:
        output_path = Path(args.output).resolve()
        output_path.parent.mkdir(parents=True, exist_ok=True)
        with output_path.open("w", encoding="utf-8") as f:
            f.write(result)
        print(f"Expanded output written to: {output_path}")
    else:
        sys.stdout.write(result)


if __name__ == "__main__":
    main()
