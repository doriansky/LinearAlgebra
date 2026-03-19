---
name: template-instantiation
description: Use when adding a new template function, operator overload, or supported type to Vector, Matrix, or MatrixToolbox. Prevents LNK2019 linker errors from missing explicit instantiations.
---

## When to use this skill

Trigger this skill whenever you:
- Add a new free function to `MatrixToolbox`
- Add a new member-template operator to `Vector` or `Matrix`
- Add a new supported scalar type (e.g. `__int128`, `float16`)

## Files that must be kept in sync

| Instantiation file (`.hpp`) | Included at bottom of |
|---|---|
| `LinearAlgebra/include/VectorExplicitTemplateInstantiations.hpp` | `LinearAlgebra/src/Vector.cpp` |
| `LinearAlgebra/include/MatrixExplicitTemplateInstantiations.hpp` | `LinearAlgebra/src/Matrix.cpp` |
| `LinearAlgebra/include/MatrixHelpersExplicitTemplateInstantiations.hpp` | `LinearAlgebra/src/MatrixToolbox.cpp` |

The `.hpp` files are `#include`d inside the `.cpp` at the bottom, inside the active namespace. They contain `template` lines (not `extern template`) that force the compiler to emit definitions.

## Pattern variants

### Single-type toolbox function (one line per scalar type)
```cpp
template ReturnType myFunction(const Matrix<int>&);
template ReturnType myFunction(const Matrix<float>&);
template ReturnType myFunction(const Matrix<double>&);
template ReturnType myFunction(const Matrix<long double>&);
```

### Two-type function (`solve`, `fit_LLSQ`, triangular solvers) — 4×4 = 16 lines
```cpp
template ReturnType myFunc(const Matrix<int>&,    Vector::Vector<int> const&);
template ReturnType myFunc(const Matrix<int>&,    Vector::Vector<float> const&);
template ReturnType myFunc(const Matrix<int>&,    Vector::Vector<double> const&);
template ReturnType myFunc(const Matrix<int>&,    Vector::Vector<long double> const&);
// repeat for Matrix<float>, Matrix<double>, Matrix<long double>
```

### Member-template operator (Vector / Matrix cross-type arithmetic)
```cpp
template Vector<std::common_type<int,float>::type> Vector<int>::operator+<float>(Vector<float> const&) const;
```
Note the `Class<T>::operatorXX<U>(...)` syntax — the template argument on the operator name is required.

## Checklist

1. Add lines to the appropriate `*ExplicitTemplateInstantiations.hpp`
2. Verify the `#include` at the bottom of the matching `.cpp` is already present (it always is)
3. Build: `cmake --build build --config Debug`
4. Confirm no `LNK2019` — if one appears, re-check the exact return type and parameter types match the declaration in the header
