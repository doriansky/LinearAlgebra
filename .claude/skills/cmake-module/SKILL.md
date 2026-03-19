---
name: cmake-module
description: Use when adding a new .cpp source file to the LinearAlgebra library or a new test .cpp to the LinearAlgebraTests executable. Both CMakeLists files use hard-coded source lists — files not registered will silently not link.
---

## Why this matters

Both `CMakeLists.txt` files use hard-coded file lists, not `GLOB`. The `file(GLOB SOURCES ...)` variable in each file is **unused** — it is not passed to `add_library` or `add_executable`. A new `.cpp` that is written but not registered will compile on first use but never link, producing a confusing `LNK2019` or a test suite that never runs.

## Adding a source file to the library

Edit `LinearAlgebra/CMakeLists.txt`, append to `add_library`:

```cmake
add_library(${library_name} SHARED
        src/Vector.cpp
        src/Matrix.cpp
        src/MatrixToolbox.cpp
        src/MyNewSource.cpp       # <-- add here
)
```

`CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON` is already set — no `__declspec(dllexport)` is needed for new symbols.

## Adding a test file to the test executable

Edit `LinearAlgebraTests/CMakeLists.txt`, append to `add_executable`:

```cmake
add_executable(${executable_name}
        src/main.cpp
        ...
        src/Matrix_QR_Factorization.cpp
        src/MyNewFunctionTests.cpp    # <-- add here
)
```

## After editing either CMakeLists file

Re-run configure before building — a stale CMake cache does **not** pick up new source registrations:

```bash
cmake -S . -B build
cmake --build build --config Debug
```

## Verification

Build completes with no `LNK2019`. If a `LNK2019` remains after registering the file, the issue is almost certainly a missing explicit template instantiation — see the **template-instantiation** skill.
