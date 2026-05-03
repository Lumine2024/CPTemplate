---
name: cptemplate-repo-context
description: Repository-specific operating guide for the CPTemplate C++ competitive programming template. Use when working in this repo to understand its architecture, choose the correct build/test workflow, avoid breaking the CMake and CI setup, handle expanded-vs-raw test modes correctly, and respect known pitfalls such as compiler switches invalidating the build directory, mandatory -Compiler usage in pwsh/ci.ps1, and the usual preference for -TestWithoutExpand unless expansion behavior itself is being changed or verified.
---

# CPTemplate Repo Context

Follow this skill whenever you modify, test, refactor, or review code in this repository.

## Read this repo as two parallel products

- Treat `include/` plus `tests/` as the executable template codebase.
- Treat `docs/` as the readable/printable documentation track.
- Remember that the repo supports both direct compilation of raw test sources and compilation of expanded single-file sources.
- Preserve that dual-track design. Do not optimize one path while silently breaking the other.

## Keep the architecture map in mind

- `include/`: reusable headers grouped by topic such as `ds`, `graph`, `math`, `str`, `geo`.
- `tests/`: one `.cpp` test per feature/topic, discovered by CMake.
- `pwsh/ci.ps1`: canonical local CI entrypoint. Prefer this over ad-hoc build commands when validating changes.
- `pwsh/expand.ps1` and `pwsh/expand.operation.ps1`: header expansion pipeline for OJ-style single-file output.
- `pwsh/expand_banzi.ps1`: documentation expansion pipeline for `docs/板子.pre-expand.md` into `docs/板子.md`.
- `CMakeLists.txt`: root build policy, optimization-level control, include path setup.
- `tests/CMakeLists.txt`: switch between raw tests and expanded tests using `CP_TEMPLATE_USE_EXPANDED_TESTS`.
- `.github/workflows/ci.yml`: authoritative statement of what CI expects to pass.

## Understand the CMake model before editing it

- The root `CMakeLists.txt` enforces C++20.
- The cache variable `CP_TEMPLATE_OPTIMIZE_LEVEL` is restricted to `0`, `1`, or `2`.
- The root CMake intentionally strips preexisting optimization flags and then reapplies the repo-controlled optimization level.
- Do not add compiler-specific optimization flags casually in test targets or per-file code unless there is a strong reason and CI implications are understood.
- `include/` is globally added as an include directory for the project.

## Understand the two test modes

- Raw mode: `tests/CMakeLists.txt` recursively builds normal `tests/**/*.cpp`, excluding generated or build-artifact paths.
- Expanded mode: `pwsh/ci.ps1 -TestWithExpand` creates `tests/expanded/`, copies `tests/expanded_cmakelists.txt` into it, expands every test source, and builds those expanded files instead.
- Use raw mode to validate template headers and normal development changes.
- Use expanded mode to validate OJ-style expansion correctness, include resolution, and single-file compatibility.
- Do not edit `tests/expanded/` by hand. It is generated and also ignored by git.

## Use `pwsh/ci.ps1` as the safe default

- Prefer `pwsh/ci.ps1` over manually reusing `cmake -B build` when you need trustworthy validation.
- Always pass `-Compiler`. It is mandatory.
- Valid compiler values are `gcc`, `clang`, `msvc`, and `clang-cl`.
- If neither `-TestWithExpand` nor `-TestWithoutExpand` is passed, the script defaults to `-TestWithExpand`.
- In normal iteration, prefer explicitly passing `-TestWithoutExpand` so validation targets the raw source tree and avoids unnecessary expansion work.
- Use `-TestWithExpand` when changing include structure, expansion logic, files used by expansion, or anything that may behave differently after header flattening.
- Pass `-OptimizeLevel 0|1|2` when reproducing CI-sensitive behavior.

## Respect the build-directory rule

- Treat `build/` as disposable.
- `pwsh/ci.ps1` always deletes and recreates `build/` before configure. This is intentional.
- Do not assume an existing `build/` directory remains valid after changing compiler, generator, or major CMake variables.
- If the compiler changes, do not try to “repair” the existing build tree with ad-hoc CMake commands. Recreate it, or just use `pwsh/ci.ps1`.
- This rule exists because switching compilers in-place is a known source of false failures and misleading diagnostics in this repo.

## Respect the compiler-specific setup

- For `msvc`, `pwsh/ci.ps1` initializes the Visual Studio toolchain environment through `vcvars64.bat` before configuring CMake.
- Do not replace the repo’s `msvc` path with a naive `cmake -D CMAKE_CXX_COMPILER=cl` flow unless you also handle environment setup correctly.
- For non-`msvc` compilers, the script passes `CMAKE_C_COMPILER` and `CMAKE_CXX_COMPILER` explicitly.
- If a build failure appears compiler-specific, reproduce it through `pwsh/ci.ps1` with the exact compiler name rather than guessing from a stale local build directory.

## Treat GitHub Actions as the source of truth

- CI runs both expanded and non-expanded modes.
- CI runs optimization levels `0`, `1`, and `2`.
- CI covers Ubuntu `gcc` and `clang`, plus Windows `msvc`, `clang`, `gcc`, and `clang-cl`, according to `.github/workflows/ci.yml`.
- Before declaring a change safe, think in terms of that matrix, not just the current local compiler.

## Preserve expansion compatibility

- `pwsh/expand.operation.ps1` resolves quoted includes by relative path, include directories, and finally bare filename lookup.
- It removes `#pragma once` during flattening and deduplicates already included files.
- Avoid introducing include patterns that only work in one environment or depend on fragile path assumptions.
- If you add headers with duplicate basenames in different directories, expansion may become ambiguous for bare filename includes.
- Prefer includes that remain unambiguous after flattening.

## Preserve documentation-generation compatibility

- `pwsh/expand_banzi.ps1` generates `docs/板子.md` from `docs/板子.pre-expand.md`.
- `docs/板子.md` is auto-generated. Do not manually edit generated content there.
- If a change affects documented snippets or documentation-backed code examples, consider whether `expand_banzi.ps1` must be rerun.
- `pwsh/push.ps1` reruns `expand_banzi.ps1` automatically after CI simulation.

## Use a safe working routine

1. Read the relevant header, test, and build script before editing.
2. Infer whether the change affects raw mode, expanded mode, docs generation, or several of them.
3. Edit the minimal set of source files.
4. Validate with `pwsh/ci.ps1 -Compiler <name> -TestWithoutExpand` first unless expansion behavior is part of the change.
5. Run `pwsh/ci.ps1 -Compiler <name> -TestWithExpand` when include/expansion safety matters.
6. If build behavior differs by compiler, rerun with the target compiler instead of patching around the symptom.

## Avoid these common mistakes

- Do not switch compilers against an old `build/` directory and trust the result.
- Do not call `pwsh/ci.ps1` without `-Compiler`.
- Do not rely on the script defaulting to expanded mode unless that is actually what you want.
- Do not edit generated `tests/expanded/` outputs.
- Do not edit generated `docs/板子.md` directly.
- Do not add CMake or source changes that only pass one mode when the repo intentionally supports both.
- Do not assume a local one-command `cmake --build build` result is equivalent to repo CI coverage.

## Prefer these commands

```powershell
./pwsh/ci.ps1 -Compiler gcc -TestWithoutExpand
./pwsh/ci.ps1 -Compiler gcc -TestWithExpand
./pwsh/ci.ps1 -Compiler msvc -OptimizeLevel 2 -TestWithoutExpand
./pwsh/expand.ps1 tests/ds/dsu.cpp -o out.cpp -I include
./pwsh/expand_banzi.ps1
```

## Escalate carefully when touching infrastructure

- Pause and reread `README.md`, `.github/workflows/ci.yml`, `CMakeLists.txt`, and `tests/CMakeLists.txt` before changing build logic, compiler handling, expansion flow, or test discovery.
- When proposing infra changes, explain how they affect raw tests, expanded tests, compiler selection, and CI parity.
- Prefer small, reversible infrastructure edits with direct validation.
