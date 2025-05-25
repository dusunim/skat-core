[![build](https://github.com/dusunim/skat-core/actions/workflows/build.yml/badge.svg)](https://github.com/dusunim/skat-core/actions/workflows/build.yml)
[![daily-build](https://github.com/dusunim/skat-core/actions/workflows/daily-build.yml/badge.svg)](https://github.com/dusunim/skat-core/actions/workflows/daily-build.yml)
[![release](https://github.com/dusunim/skat-core/actions/workflows/release.yml/badge.svg)](https://github.com/dusunim/skat-core/actions/workflows/release.yml)

# skat-core

**skat-core** is the skeleton of a shared core library designed to support all products derived from the SKAT platform.  
It lays the groundwork for collecting common modules, utilities, and constants that will be shared across the entire SKAT ecosystem.

Although currently minimal, this repository defines the structure and direction for future development of reusable and standardized components.

## Features

- Centralized core functionality shared across all products derived from the SKAT platform
- Minimal dependencies and lightweight structure
- Fast builds supported via [binary caching](https://learn.microsoft.com/en-us/vcpkg/users/binarycaching) in the cloud through GitHub Actions workflows

## Getting Started
### Clone the repository

```bash
$ git clone https://github.com/dusunim/skat-core.git
$ cd skat-core
$ git submodule update --init
```

## Build Instructions
### For Linux and macOS
Use the ninja preset for a fast and consistent build:
```bash
$ cmake --preset ninja
$ cmake --build --preset ninja/release
```

### For Windows
You can use ninja as on other platforms, or alternatively use the Visual Studio generator for IDE integration:
```bash
$ cmake --preset vs
```

Then you can either build directly inside Visual Studio, or use the command line:

```bash
$ cmake --build --preset ninja/release
```

## Release Process
Releases are automatically built and published through GitHub Actions when a Git tag is pushed in `release/x.y.z` format. Where `x`, `y`, and `z` are integers representing the **major**, **minor**, and **patch** versions respectively.


Example:
```bash
$ git tag release/1.0.0
$ git push origin release/1.0.0
```
Then the CI workflow will automatically build and package the release.
