# Task List: Missing LinearAlgebra Functionality

## Context
The library currently covers basic vector/matrix arithmetic, LU/QR decompositions, RREF, rank, determinant, inversion (full/left/right), a general Ax=b solver, triangular solvers, and least-squares fitting. The tasks below fill in the most commonly needed gaps in a complete linear algebra library.

---

## Decompositions

### T1 — Cholesky Decomposition
**What:** Decompose a symmetric positive-definite (SPD) matrix as A = L·Lᵀ (or L·Lᴴ for Hermitian complex).
**New struct:** `CholeskyFactorization { Matrix<long double> L; }`.
**Functions:** `factorizeCholesky(const Matrix<T>&) -> std::optional<CholeskyFactorization>` (returns nullopt if matrix is not SPD).
**Bonus solver:** `solveCholesky(const CholeskyFactorization&, const Vector<U>&)` — faster than LU for SPD systems.
**Files:** `MatrixToolbox.hpp`, `MatrixToolbox.cpp`, new test file `MatrixCholesky.cpp`.

### T2 — Singular Value Decomposition (SVD)
**What:** Decompose any m×n matrix as A = U·Σ·Vᵀ.
**New struct:** `SVDFactorization { Matrix<long double> U; Matrix<long double> Sigma; Matrix<long double> V; }`.
**Functions:** `factorizeSVD(const Matrix<T>&) -> SVDFactorization`.
**Derived utilities** (can be free functions using SVD):
- `singularValues(const Matrix<T>&) -> Vector<long double>`
- `conditionNumber(const Matrix<T>&) -> long double`
- `pseudoInverse(const Matrix<T>&) -> Matrix<long double>` (Moore–Penrose)
**Files:** `MatrixToolbox.hpp`, `MatrixToolbox.cpp`, new test file `MatrixSVD.cpp`.

### T3 — Eigenvalue Decomposition
**What:** For a square diagonalizable matrix, compute eigenvalues and eigenvectors.
**New struct:** `EigenDecomposition { Vector<std::complex<long double>> eigenvalues; Matrix<std::complex<long double>> eigenvectors; }`.
**Function:** `eigenDecompose(const Matrix<T>&) -> EigenDecomposition`.
**Note:** Implement via QR iteration (builds on existing `factorizeQR`).
**Files:** `MatrixToolbox.hpp`, `MatrixToolbox.cpp`, new test file `MatrixEigenDecomposition.cpp`.

---

## Matrix Properties & Checks

### T4 — Missing Property Checks
Add to `MatrixToolbox.hpp/.cpp`:
- `isSymmetric(const Matrix<T>&, T tol) -> bool`
- `isHermitian(const Matrix<std::complex<U>>&, U tol) -> bool`
- `isOrthogonal(const Matrix<T>&, T tol) -> bool` (AᵀA = I)
- `isUnitary(const Matrix<std::complex<U>>&, U tol) -> bool`
- `isPositiveDefinite(const Matrix<T>&) -> bool` (via Cholesky attempt)
- `isDiagonal(const Matrix<T>&, T tol) -> bool`
**Files:** `MatrixToolbox.hpp`, `MatrixToolbox.cpp`, extend `MatrixHelpersTests.cpp`.

### T5 — Matrix Norms & Trace
Add to `MatrixToolbox.hpp/.cpp`:
- `trace(const Matrix<T>&) -> T`
- `normFrobenius(const Matrix<T>&) -> long double`
- `norm1(const Matrix<T>&) -> long double` (max column sum)
- `normInf(const Matrix<T>&) -> long double` (max row sum)
- `norm2(const Matrix<T>&) -> long double` (largest singular value — depends on T2)
**Files:** `MatrixToolbox.hpp`, `MatrixToolbox.cpp`, extend `MatrixHelpersTests.cpp`.

---

## Matrix Manipulation

### T6 — Column & Submatrix Access
Add to `MatrixToolbox.hpp/.cpp`:
- `getCol(const Matrix<T>&, unsigned int col) -> Vector<T>`
- `setCol(Matrix<T>&, const Vector<T>&, unsigned int col)`
- `swapCols(Matrix<T>&, unsigned int col1, unsigned int col2)`
- `subMatrix(const Matrix<T>&, unsigned int rowStart, unsigned int rowEnd, unsigned int colStart, unsigned int colEnd) -> Matrix<T>`
**Files:** `MatrixToolbox.hpp`, `MatrixToolbox.cpp`, extend `MatrixHelpersTests.cpp`.

### T7 — Diagonal & Construction Helpers
Add to `MatrixToolbox.hpp/.cpp`:
- `diagonal(const Vector<T>&) -> Matrix<T>` (build diagonal matrix from vector)
- `getDiagonal(const Matrix<T>&) -> Vector<T>` (extract main diagonal)
- `hstack(const Matrix<T>&, const Matrix<T>&) -> Matrix<T>` (horizontal concatenation)
- `vstack(const Matrix<T>&, const Matrix<T>&) -> Matrix<T>` (vertical concatenation)
**Files:** `MatrixToolbox.hpp`, `MatrixToolbox.cpp`, extend `MatrixHelpersTests.cpp`.

---

## Vector Operations

### T8 — Missing Vector Utilities
Add to `Vector.hpp/.cpp`:
- `normalize() -> Vector<long double>` (unit vector, wraps `norm()`)
- `sum() -> T`
- `min() -> T` / `max() -> T`
- `abs() -> Vector<T>` (element-wise absolute value)
Add free functions:
- `cross(const Vector<T>&, const Vector<U>&) -> Vector<common_type>` (3D only, throws for other dims)
- `outer(const Vector<T>&, const Vector<U>&) -> Matrix<common_type>` (outer product → Matrix)
- `projection(const Vector<T>& u, const Vector<U>& onto) -> Vector<long double>` (proj_onto(u))
**Files:** `Vector.hpp`, `Vector.cpp`, extend `VectorTests.cpp`.

---

## Complex-Specific

### T9 — Conjugate Transpose (Hermitian Adjoint)
Add to `MatrixToolbox.hpp/.cpp`:
- `conjugateTranspose(const Matrix<std::complex<T>>&) -> Matrix<std::complex<T>>` (also called adjoint or dagger A†)
Add to `Vector.hpp/.cpp`:
- `conjugate() -> Vector<std::complex<T>>` (element-wise conjugate)
**Files:** `MatrixToolbox.hpp`, `MatrixToolbox.cpp`, `Vector.hpp`, `Vector.cpp`.

---

## Implementation Order (Recommended)

1. **T6, T7** — foundational helpers needed by later tasks
2. **T4, T5** — property checks and norms (self-contained)
3. **T8, T9** — vector utilities and complex adjoint
4. **T1** — Cholesky (simpler decomposition, good stepping stone)
5. **T2** — SVD (most impactful; enables condition number, pseudoinverse, norm2)
6. **T3** — Eigenvalue decomposition (most complex; builds on QR iteration)
