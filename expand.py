#!/usr/bin/env python3
"""expand.py - Expand local #include directives in C++ files.

Usage:
    python expand.py <input_file> [-o <output_file>]

This script recursively expands all #include "..." (local/quoted includes)
by inlining the referenced file content, while leaving #include <...>
(system includes) unchanged. Each local file is included at most once,
respecting #pragma once semantics.

Example:
    python expand.py usage/geo/rotcal.cpp -o contest/D.cpp
"""

import argparse
import os
import re
import sys


def expand(filepath: str, included: set) -> str:
    """Recursively expand local includes in a file.

    Args:
        filepath: Path to the C++ source file to expand.
        included: Set of absolute paths already included (for #pragma once).

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
            full_include = os.path.normpath(os.path.join(file_dir, include_path))
            expanded = expand(full_include, included)
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
    args = parser.parse_args()

    if not os.path.isfile(args.input):
        print(f"Error: '{args.input}' is not a file or does not exist.", file=sys.stderr)
        sys.exit(1)

    included: set = set()
    result = expand(args.input, included)

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
