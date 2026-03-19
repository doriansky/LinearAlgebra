---
name: build-troubleshooting
description: Use when the build fails unexpectedly after a CMakeLists change, branch switch, or Debug/Release config change.
---

## MSVC multi-config output layout

Binaries land in a config-specific subdirectory, **not** directly in `bin/`:

```
bin/Debug/LinearAlgebraTests.exe
bin/Debug/LinearAlgebra.dll
bin/Release/LinearAlgebraTests.exe
```

Always run:
```bash
./bin/Debug/LinearAlgebraTests.exe     # Debug build
./bin/Release/LinearAlgebraTests.exe   # Release build
```

The `CLAUDE.md` example `./bin/LinearAlgebraTests` is the Linux/non-MSVC path — on Windows use the subdirectory.

## Clean rebuild

When the build behaves unexpectedly (stale targets, wrong config, missing symbols after a branch switch):

```bash
# From repo root
rm -rf build/
cmake -S . -B build
cmake --build build --config Debug
```

## Stale cache symptoms

| Symptom | Cause | Fix |
|---|---|---|
| "Target not found" or old removed file still compiling | CMake cache from previous config | Clean rebuild |
| New `.cpp` not compiled | File added to disk but not to CMakeLists | See **cmake-module** skill |
| `LNK2019` after adding a new function | Missing explicit template instantiation | See **template-instantiation** skill |
| `LNK2005` duplicate symbol | Same instantiation listed in two `.cpp` files | Remove duplicate from one of the `*ExplicitTemplateInstantiations.hpp` files |

## LNK2019 decision tree

1. Is the function declared in the header but not defined in any `.cpp`? → Add definition to `MatrixToolbox.cpp`
2. Is the function defined but the explicit instantiation missing? → Add to `MatrixHelpersExplicitTemplateInstantiations.hpp`
3. Is the source `.cpp` registered in `CMakeLists.txt`? → If not, see **cmake-module** skill
4. Does the instantiation line's return type / parameter types exactly match the declaration? → Fix the mismatch
