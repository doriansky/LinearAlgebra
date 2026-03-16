# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

This project uses CMake with a build directory separate from the source tree.

```bash
# Configure (from repo root)
cmake -S . -B build

# Build
cmake --build build

# Output goes to ./bin/
```

Compiler flags: `-Wall -Werror` — all warnings are treated as errors.

## Tests

Tests use Google Test. After building:

```bash
# Run all tests
./bin/LinearAlgebraTests

# Run a single test or filter by name
./bin/LinearAlgebraTests --gtest_filter=<TestSuiteName>.<TestName>
```

## Architecture

### Library structure

The library is a shared library (`LinearAlgebra`) with two core template classes and a toolbox of free functions:

- **`LinearAlgebra::Vector::Vector<T>`** (`LinearAlgebra/include/Vector.hpp`) — n-dimensional vector. Supports element-wise arithmetic, dot product (with complex support), and norm. The `operator*` between two vectors is element-wise, not a dot product.
- **`LinearAlgebra::Matrix::Matrix<T>`** (`LinearAlgebra/include/Matrix.hpp`) — 2D matrix in row-major storage. `operator*` between matrices is also element-wise; matrix multiplication is a separate overload that calls `operator*(Matrix)`, and matrix-vector multiplication is `operator*(Vector)`. Has a specialization for `Matrix<std::complex<U>>`.
- **`MatrixToolbox`** (`LinearAlgebra/include/MatrixToolbox.hpp`) — free functions for all advanced operations: LU/QR factorization, RREF, pivots, rank, determinant, inverse (including left/right inverses for rectangular matrices), general linear system solver, triangular solvers, and least-squares fitting.

### Key return types (in MatrixToolbox)

| Struct | Fields |
|---|---|
| `LUFactorization` | `lower`, `upper`, optional `permutation`, optional `pSign` |
| `QRFactorization` | `Q` (orthonormal), `R` (upper triangular) |
| `Solution` | `unique` flag, `uniqueSolution`, `particularSolution`, `specialSolutions` |
| `FitLLSQ` | `bestEstimate`, `error` |
| `Pivot` | `value`, `rowIndex`, `colIndex` |

### Template instantiation

Explicit template instantiations are declared in `*ExplicitTemplateInstantiations.hpp` files and defined in the corresponding `.cpp` files. When adding new type combinations, register them in these files to avoid linker errors.

### Mixed-type arithmetic

Arithmetic between `Vector<T>` and `Vector<U>` (or with scalars) returns `Vector<std::common_type_t<T,U>>`. Same pattern applies to `Matrix`.
