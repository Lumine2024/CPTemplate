<h1 align="center"> CPTemplate </h1>

<p align="center">
  面向 ICPC/OI 的 C++ 竞赛模板工程
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

面向 ICPC/OI 的 C++ 竞赛模板工程。这个仓库既提供可阅读、可打印的文档版本，也提供可测试、可展开、可直接提交的代码版本。

## 快速导航

| 内容 | 入口 |
| --- | --- |
| 主模板文档（Markdown） | [docs/板子.md](docs/板子.md) |
| 主模板文档（PDF） | [docs/板子.pdf](docs/板子.pdf) |
| 公式文档 | [docs/公式.md](docs/公式.md) |
| 崩溃与退出码说明 | [docs/退出码与崩溃原因.md](docs/退出码与崩溃原因.md) |
| 模板头文件 | [include/](include/) |
| 单文件展开脚本 | [pwsh/expand.ps1](pwsh/expand.ps1) |
| CI 测试脚本 | [pwsh/ci.ps1](pwsh/ci.ps1) |

## 项目特性

1. 工程化组织
采用按主题分层的目录结构（如 `graph`、`ds`、`math`），便于查找、复用与维护。

2. 竞赛友好的 API 封装
常用数据结构和算法接口做了统一封装，减少现场手写细节导致的失误。

3. 一致的索引与区间约定
默认使用 0-indexed 与左闭右开区间，和 STL 使用习惯一致。

4. 自动化展开与测试
提供头文件展开脚本与 CI 脚本，支持本地快速验证模板正确性。

5. 文档与代码双轨维护
文档用于赛前复习和打印，代码用于本地调试与在线评测提交。

## 目录结构

```text
CPTemplate/
|- docs/               # 模板与公式文档（md/html/pdf）
|- image_assets/       # 文档图片资源
|- include/            # 竞赛模板头文件
|- pwsh/               # PowerShell 自动化脚本
|- python/             # Python 工具脚本
|- tests/              # 单元测试与测试用例
|- CMakeLists.txt
|- README.md
`- README_EN.md
```

## 环境要求

1. C++20 及以上编译器（gcc/clang/msvc 均可）
2. CMake 3.20+
3. Ninja（推荐）
4. PowerShell 7+

## 快速开始

### 1) 本地构建

```powershell
cmake -S . -B build -G Ninja -D CMAKE_BUILD_TYPE=Release
cmake --build build -j
```

### 2) 运行测试（推荐）

```powershell
./pwsh/ci.ps1 -Compiler gcc
```

常用参数：
1. `-TestWithExpand`：测试前先展开（默认开启）
2. `-TestWithoutExpand`：跳过展开，直接测原始文件
3. `-Compiler clang|gcc|msvc|clang-cl`：切换编译器

### 3) 展开单个源文件（用于提交 OJ）

```powershell
./pwsh/expand.ps1 tests/ds/dsu.cpp -o out.cpp -I include
```

### 4) 展开模板文档中的引用片段

```powershell
./pwsh/expand_banzi.ps1
```

## 设计原则

1. 可读性优先于过度技巧化
2. 接口稳定优先于局部微优化
3. 模块独立，避免隐式依赖
4. 先可验证，再可复用

## 贡献说明

当前仓库以个人学习与整理为主，暂不直接接受代码 PR。

如果你希望基于本模板修改，请先 Fork 后在自己的仓库维护。

若你有希望补充的板子或专题，欢迎提交 Issue：

[https://github.com/Lumine2024/CPTemplate/issues/new](https://github.com/Lumine2024/CPTemplate/issues/new)
