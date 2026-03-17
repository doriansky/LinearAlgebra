---
name: documentation
description: Use when asked to write or review documentation for C++ code, including new or existing functions, classes, and structs.
---

## When to Document

- **Always document**: Public API functions declared in `.hpp` files, free functions in `MatrixToolbox.hpp`, structs with semantic meaning.
- **Document when non-obvious**: Complex algorithms, non-trivial parameter constraints, mathematical identities, side effects, solvability conditions.
- **Minimal or no documentation for**: Trivial getters/setters, constructors/destructors (use a brief grouping label instead), private implementation details, operator overloads whose semantics are self-evident from the signature.

---

## File Header

Every `.hpp` and `.cpp` file starts with the same author/date block using `//` comments:

```cpp
//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//
```

---

## Function Documentation Format

Use a Javadoc-style block comment (`/** ... */`) placed **above the declaration in the `.hpp` file**. Never duplicate documentation in the `.cpp` definition.

### Tag reference

| Tag | Format | Notes |
|-----|--------|-------|
| Description | First line, no tag | One or more lines describing purpose |
| `@param:` | `@param: <Type> : <description>` | Include the full type before the colon |
| `@return:` | `@return: <Type>: <description>` | Include the return type before the colon |

> **Note:** This codebase uses Javadoc-style `@param`/`@return` with a colon suffix — not Doxygen backslash syntax (`\param`, `\brief`). Do not use `@brief`, `///`, or `\` prefixes.

### Minimal example — free function

```cpp
/**
* Generate the identity matrix
*
* @return: Matrix: identity matrix of specified dimension
*/
template <typename T>
Matrix<T> identity(unsigned int);
```

### Standard example — operator with mixed types

```cpp
/**
* Operators for matrix arithmetic : addition and subtraction
* The two matrices can have different types.
*
* @param: const Matrix<U>& : the other matrix
* @return: Matrix<typename std::common_type<T,U>::type>: the result of the +, - operation
*/
template<class U>
Matrix<typename std::common_type<T,U>::type> operator+(const Matrix<U>& other) const;
```

### Extended example — algorithm with multiple return fields

For complex return types (structs with several optional fields), document each field inline within the `@return` block:

```cpp
/**
* Factorize the matrix into Lower and Upper matrices (and an optional permutation matrix) such that A = L*U
* or P*A = L*U when row exchanges are required.
*
* NOTE : For singular or rectangular matrices the function will return as soon as a column is found with zeros below the pivot.
*        The lower and "partial" upper factorization will still reconstruct the input matrix but the U will not be a fully upper matrix.
*        Therefore, for singular or rectangular matrices one can use LU_echelon() instead.
*
* @return: struct containing lower triangular matrix, upper triangular matrix and the optional permutation matrix
*          lower:          the L matrix is square, numRows x numRows
*          upper:          the U matrix has the same dimensions as the input, numRows x numCols
*          permutation:    the optional P matrix (if has value) is square, numRows x numRows
*          pSign:          the optional sign of the permutation (+1/-1 for even/odd row swaps)
*/
template <typename T>
[[nodiscard]] LUFactorization factorizeLU(const Matrix<T>&);
```

### Extended example — solvability conditions in `@return`

When a function returns `std::optional` and has non-trivial solvability conditions, document all cases:

```cpp
/**
* Solve system of linear equations Ax = b and return the solution x
*
* @param: const Vector::Vector<U>: the "b" column vector
* @return: std::optional<Solution> solution : a struct containing the following fields:
*               bool                                            unique;             // indicates if the system has unique solution.
*               std::optional<Vector<long double>>              uniqueSolution;     // unique solution to Ax=b when "unique" is true
*               std::optional<Vector<long double>>              particularSolution; // particular solution when "unique" is false
*               std::optional<std::vector<Vector<long double>>> specialSolutions;   // (numCols - rank) solutions to Ax=0
*
*               If the system is not solvable, std::nullopt is returned. If solvable, 4 cases:
*               a) R = numRows and R = numCols  : unique solution for ANY b
*               b) R < numRows and R = numCols  : unique solution if b is in the column space of A
*               c) R = numRows and R < numCols  : infinitely many solutions for ANY b
*               d) R < numRows and R < numCols  : infinitely many solutions if b is in the column space of A
*/
template<typename T, typename U>
[[nodiscard]] std::optional<Solution> solve(const Matrix<T>&, const Vector::Vector<U>&);
```

---

## Grouping Labels in Headers

For operator and method groups that do not need full Javadoc, use a short `//` label above the group. This is the standard pattern in `Vector.hpp` and `Matrix.hpp`:

```cpp
//Copy and move constructor
Vector(const Vector&);
Vector(Vector&&) noexcept;

//Copy assignment and move assignment
Vector& operator=(const Vector& other);
Vector& operator=(Vector&& other) noexcept;

//Getters
[[nodiscard]] unsigned int dim() const;

//Array subscript
const T& operator[] (unsigned int) const;
T& operator[]       (unsigned int);

//Binary arithmetic
template<class U>
Vector<typename std::common_type<T,U>::type> operator+(const Vector<U>& other) const;

//In-place operations with another Vector (OF THE SAME TYPE !)
Vector& operator+=(const Vector& other);

//Broadcasters
template<class U>
Vector<typename std::common_type<T,U>::type> operator+(U val) const;
```

For non-member operators, add a brief note explaining the intended syntax:

```cpp
// Non-member functions that allow writing code with the following syntax:
// result = 2 + myVector;
template<typename T, typename U>
Vector<typename std::common_type<T,U>::type> operator+(T val, const Vector<U>&);
```

---

## Section Separators in `.cpp` Files

Use repeated-slash separators to mark the start and end of major implementation blocks (e.g., a template specialization):

```cpp
//////////////////////////////////////////////// COMPLEX MATRIX
template <typename U>
Matrix<std::complex<U>>::Matrix(...)
{
    // ...
}
//////////////////////////////////////////////// END COMPLEX MATRIX
```

---

## Implementation Comments in `.cpp` Files

Document algorithm steps with `//` comments. Write them as active-verb phrases that explain *why* or *what*, not just what the next line does literally.

### Explain non-obvious design decisions

```cpp
//Use Scott Meyers's trick and make this operator call the const version of operator(row,col)
return const_cast<T&>(static_cast<const Matrix<T>&>(*this)(rowIdx, colIdx));
```

### Label steps of a multi-step algorithm

```cpp
//Search first non-zero in the current row
const auto pivotIt = std::find_if(upper.begin() + startIdx, upper.begin() + endIdx,
                                  [](const auto& val) { return std::abs(val) > 1e-9; });

// Iterate pivots in reverse order !
for (auto it = pivots.rbegin(); it != pivots.rend(); ++it)

//Divide by pivots
std::transform(rre.begin() + startIdx, rre.begin() + endIdx, &rre(0,0) + startIdx,
               [pivotValue](auto& val) { return val / pivotValue; });

//Create zeros above the pivots
for (const auto pivot : pivots)
```

### Explain IIFE usage

```cpp
// If row-exchanges were done during forward elimination, the permutation matrix must be applied on the b vector !
// IIFE for the win
const auto c = [&]
{
    if (LU.permutation)
        return solveLowerTriangular(LU.lower, LU.permutation.value() * b);
    else
        return solveLowerTriangular(LU.lower, b);
}();
```

### Flag TODOs

```cpp
//  Current pivot is zero, search non-zero values in below entries
// TODO consider swapping with the row having the biggest value in the current column
if (auto rowIdxToSwap = findNonZeroPivot(result.upper, i, i))
```

---

## What NOT to Document

- **Private data members** — no comments needed on `std::vector<T> data` or `unsigned int numRows`.
- **Trivial constructors / destructors** — label the group, but do not add a Javadoc block.
- **`.cpp` definitions** — do not copy or summarize the `.hpp` documentation in the implementation file.
- **Self-evident one-liners** — if the function name and signature fully convey intent, a comment adds noise.

---

## Best Practices

1. **Parameter alignment**: Align `@param:` type columns with spaces for readability when there are multiple parameters.
2. **Type hints inline**: Always include the full C++ type before the colon in `@param:` and `@return:`.
3. **NOTE blocks**: Use `NOTE :` (uppercase) for important constraints or edge-case behavior, indented to align with the description body.
4. **Exclamation marks for warnings**: Use `!` at the end of constraint notes to draw attention (e.g., `The two matrices must have the same type !`).
5. **Mathematical intent**: When a function implements a known algorithm or formula, name it explicitly in the description (e.g., "Factorize the matrix into Lower and Upper matrices such that A = L*U").
