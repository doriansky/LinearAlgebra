---
name: add-toolbox-function
description: Use when adding a new mathematical free function to MatrixToolbox. Covers the five-location sequence required to avoid linker errors and silent test omissions.
---

## Prerequisites

- Refer to the **coding-guidelines** skill before writing any code.
- Refer to the **documentation** skill for Javadoc format on the new declaration.

## Five-step sequence (must follow in order)

### Step 1 — Declare in `LinearAlgebra/include/MatrixToolbox.hpp`

Inside `namespace LinearAlgebra::Matrix`, add:
```cpp
/**
 * @brief One-line summary.
 * @param A Description of parameter.
 * @return Description of return value.
 */
[[nodiscard]] ReturnType myNewFunction(const Matrix<T>& A);
```

Rules:
- Use `[[nodiscard]]` on all functions that return a result.
- Use `std::optional<T>` for fallible functions (e.g. those that may have no solution).
- For multi-value returns, define an aggregate `struct` in the same header (see `LUFactorization`, `Solution`, etc.).
- Use `camelCase` naming (avoid `snake_case` — legacy `hilbert_matrix`, `fit_LLSQ` are exceptions).

### Step 2 — Implement in `LinearAlgebra/src/MatrixToolbox.cpp`

Add the definition inside `namespace LinearAlgebra::Matrix { ... }`.

Internal helpers (not part of the public API) go in an **anonymous namespace** at the top of the file:
```cpp
namespace {
    static double helperUtil(...) { ... }
}
```

### Step 3 — Register instantiations

Add lines to `LinearAlgebra/include/MatrixHelpersExplicitTemplateInstantiations.hpp`.

See the **template-instantiation** skill for exact syntax. Single-type functions need 4 lines; two-type functions need 16 lines.

### Step 4 — Register the test file in `LinearAlgebraTests/CMakeLists.txt`

Append to `add_executable(LinearAlgebraTests ...)`:
```cmake
        src/MyNewFunctionTests.cpp
```

See the **cmake-module** skill for details. Re-run configure after editing CMakeLists.

### Step 5 — Implement tests

Create `LinearAlgebraTests/src/MyNewFunctionTests.cpp`.

Follow the **test-writer** skill. 

### Step 6 — Execute tests
Follow the **test-executor** skill to run the new tests and generate the test report.

## Verification checklist

- [ ] Declaration in `MatrixToolbox.hpp` with `[[nodiscard]]` and Javadoc
- [ ] Implementation in `MatrixToolbox.cpp` inside the correct namespace
- [ ] Instantiation lines in `MatrixHelpersExplicitTemplateInstantiations.hpp`
- [ ] Test `.cpp` registered in `LinearAlgebraTests/CMakeLists.txt`
- [ ] Tests pass: `./bin/Debug/LinearAlgebraTests.exe --gtest_filter=MyNewFunctionTests.*`
- [ ] No `LNK2019` linker errors
