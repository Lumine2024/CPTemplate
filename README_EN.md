<h1 align="center"> CPTemplate </h1>

<p align="center">
	A production-style C++ competitive programming template for ICPC/OI workflows
</p>

<p align="center">
	<a href="./README.md">简体中文</a> |
	<a href="./README_EN.md">English</a>
</p>

<p align="center">
	<a href="./LICENSE"><img src="https://img.shields.io/badge/License-MIT-1f6feb?style=flat-square" alt="MIT License"></a>
	<a href="https://github.com/Lumine2024/CPTemplate/actions/workflows/ci.yml"><img src="https://img.shields.io/github/actions/workflow/status/Lumine2024/CPTemplate/ci.yml?branch=main&label=CI&style=flat-square" alt="CI Status"></a>
	<img src="https://img.shields.io/badge/C%2B%2B-20-00599C?logo=c%2B%2B&style=flat-square" alt="C++20">
	<img src="https://img.shields.io/badge/CMake-3.16%2B-064F8C?logo=cmake&style=flat-square" alt="CMake 3.16+">
	<img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-444?style=flat-square" alt="Platform">
</p>

A production-style C++ competitive programming template repository for ICPC/OI workflows.
It provides both documentation-oriented assets (for review/printing) and code-oriented assets (for local testing and online judge submission).

## Quick Links

| Resource | Path |
| --- | --- |
| Main template doc (Markdown) | [docs/板子.md](docs/板子.md) |
| Main template doc (PDF) | [docs/板子.pdf](docs/板子.pdf) |
| Formula notes | [docs/公式.md](docs/公式.md) |
| Crash and exit-code notes | [docs/退出码与崩溃原因.md](docs/退出码与崩溃原因.md) |
| Header template library | [include/](include/) |
| Single-file expand script | [pwsh/expand.ps1](pwsh/expand.ps1) |
| CI test script | [pwsh/ci.ps1](pwsh/ci.ps1) |

## Highlights

1. Engineering-friendly structure
Modules are grouped by domain (`graph`, `ds`, `math`, etc.) for fast navigation and maintenance.

2. Contest-safe API wrappers
Frequently used implementations expose stable wrappers to reduce error-prone boilerplate during contests.

3. Consistent conventions
0-indexed and left-closed right-open intervals are used across modules, matching STL habits.

4. Automation first
Built-in expansion and CI scripts help validate correctness before submission.

5. Docs + code dual track
Use docs for review/printing, and code modules for local testing and OJ submission.

## Repository Layout

```text
CPTemplate/
|- docs/               # Template and formula docs (md/html/pdf)
|- image_assets/       # Image resources for docs
|- include/            # Header-only template modules
|- pwsh/               # PowerShell automation scripts
|- python/             # Python helper scripts
|- tests/              # Unit tests and test cases
|- CMakeLists.txt
|- README.md
`- README_EN.md
```

## Requirements

1. C++20+ compiler (gcc/clang/msvc)
2. CMake 3.20+
3. Ninja (recommended)
4. PowerShell 7+

## Getting Started

### 1) Build locally

```powershell
cmake -S . -B build -G Ninja -D CMAKE_BUILD_TYPE=Release
cmake --build build -j
```

### 2) Run tests (recommended)

```powershell
./pwsh/ci.ps1 -Compiler gcc
```

Common options:
1. `-TestWithExpand`: run tests after expansion (default)
2. `-TestWithoutExpand`: skip expansion and test raw sources
3. `-Compiler clang|gcc|msvc|clang-cl`: select compiler

### 3) Expand a single source file for OJ

```powershell
./pwsh/expand.ps1 tests/ds/dsu.cpp -o out.cpp -I include
```

### 4) Expand referenced snippets in template docs

```powershell
./pwsh/expand_banzi.ps1
```

## Design Principles

1. Readability over unnecessary trickiness
2. Stable interfaces over local micro-optimizations
3. Independent modules, minimal hidden coupling
4. Verifiability before reusability

## Contribution Policy

This repository is primarily maintained as a personal learning and engineering notebook, so direct PR contributions are currently closed.

If you want to customize this template, please fork and maintain your own branch.

Feature requests and topic requests are welcome via Issue:
[https://github.com/Lumine2024/CPTemplate/issues/new](https://github.com/Lumine2024/CPTemplate/issues/new)

## License

This project is licensed under the terms described in [LICENSE](LICENSE).

