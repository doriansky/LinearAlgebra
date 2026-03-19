---
name: coding-guidelines
description: Use when writing new C++ code or modifying existing code during implementation or refactoring tasks.
---

## General Rules

- Prefer C++ style casts (`static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`) over C-style casts.
- Target the **C++17** standard. Use its features (nested namespaces, `std::optional`, structured bindings, `std::exchange`) where they improve clarity.
- Never use `using namespace` in header files — it pollutes the namespace of every translation unit that includes them.

## Header Files

- Every `.cpp` file must have an associated `.hpp` file. Exceptions: unit test files and explicit template instantiation `.cpp` files.
- Use **both** `#ifndef`/`#define`/`#endif` guards **and** `#pragma once` in every header.
- Add a closing comment on `#endif` that repeats the guard name:
  ```cpp
  #ifndef VECTOR_HPP
  #define VECTOR_HPP
  #pragma once
  // ...
  #endif // VECTOR_HPP
  ```
- Start every file with the author/date comment block:
  ```cpp
  //
  // Created by <author> on <date>.
  // <email>
  //
  ```
- **Order of includes in `.hpp` files**: only include what is strictly needed; prefer STL headers only.
- **Order of includes in `.cpp` files**:
  1. Own header (e.g., `"Vector.hpp"`)
  2. STL and third-party headers (e.g., `<algorithm>`, `<cmath>`)
- Include the definition of a function inline in a header only when the definition is short (e.g., a trivial getter).

## Namespaces

- Use the C++17 nested namespace syntax: `namespace LinearAlgebra::Vector { }`.
- Place all library code inside the project's top-level namespace hierarchy.
- Use anonymous namespaces for file-local helper functions that must not be visible outside the translation unit:
  ```cpp
  namespace {
      std::optional<unsigned int> findNonZeroPivot(...) { ... }
  }
  ```
- Use the fully qualified name when referencing types from sibling namespaces (e.g., `Vector::Vector<T>` inside `namespace LinearAlgebra::Matrix`).

## Naming Conventions

- Use descriptive and meaningful names. Avoid cryptic abbreviations.
- `PascalCase` for class names, struct names, and namespace names.
- `camelCase` for method names, free function names, and local/member variables.
- Single uppercase letter (`T`, `U`, `V`) for template type parameters.
- `UPPER_SNAKE_CASE` for header guard macros (e.g., `VECTOR_HPP`).
- **Inconsistency to avoid**: helper functions that generate test data (e.g., `hilbert_matrix`) have historically used `snake_case` — prefer `camelCase` (`hilbertMatrix`) for all new free functions.
- Boolean-returning functions should be prefixed with `is` or `has` (e.g., `isLowerTriangular`).

## Variables

- Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.
- Always declare variables as `const`; use the IIFE idiom when direct `const` initialization requires branching:
  ```cpp
  const auto c = [&] {
      if (condition) return valueA;
      else           return valueB;
  }();
  ```
- Prefer `const auto var = expression;` over explicitly spelling out the type on the left-hand side when the type is obvious from the right-hand side.
- Use structured bindings (`const auto [a, b] = ...`) to unpack multi-value returns cleanly.

## Memory Management

- Raw pointers must never be allocated. Always use STL containers (`std::vector`) or smart pointers (`std::unique_ptr`, `std::shared_ptr`).
- If you find yourself needing a raw pointer, reconsider the design.

## Classes

- Follow the **Single Responsibility Principle**: each class has one well-defined responsibility.
- Favor free functions over member functions. A function should only be a member if it requires access to private state; otherwise make it a free function in the same namespace.
- **Class layout order**: `public` section first (constructors, destructor, operators, methods), then `private` section (data members).
- Always use `[[nodiscard]]` on functions that return a value (including operators and getters).
- Always mark member functions that do not modify state as `const`.

### Rule of Five

Whenever a class manages a resource (e.g., owns a `std::vector`), always define all five special member functions explicitly:

```cpp
Vector(const Vector&);               // Copy constructor
Vector(Vector&&) noexcept;           // Move constructor — always mark noexcept
Vector& operator=(const Vector&);    // Copy assignment
Vector& operator=(Vector&&) noexcept;// Move assignment — always mark noexcept
~Vector() = default;                 // Destructor — use = default when trivial
```

- Use `std::exchange` to null-out moved-from resource handles:
  ```cpp
  numRows = std::exchange(other.numRows, 0);
  ```
- Delete the default constructor explicitly when a default-constructed object would be meaningless:
  ```cpp
  Vector() = delete;
  ```
- Mark single-argument constructors `explicit` to prevent accidental implicit conversions.

## Operators

- Implement the `const` overload of `operator[]`/`operator()` first; implement the non-const overload by delegating to it (Scott Meyers' trick):
  ```cpp
  T& operator[](unsigned int idx) {
      return const_cast<T&>(static_cast<const Vector<T>&>(*this)[idx]);
  }
  ```
- Binary arithmetic operators between two different types must be member templates returning `std::common_type_t<T,U>`:
  ```cpp
  template<class U>
  Vector<typename std::common_type<T,U>::type> operator+(const Vector<U>& other) const;
  ```
- Provide non-member operator overloads (inside the namespace) for commutativity (e.g., `scalar + vector`).
- In-place operators (`+=`, `-=`, `*=`, `/=`) should only be provided for same-type operands and must return `*this` by reference.

## Templates and Generic Programming

- Use explicit template instantiations to keep compile times manageable. Declare instantiations in a dedicated `*ExplicitTemplateInstantiations.hpp` header and define them in a paired `.cpp`:
  ```cpp
  // In header:
  extern template class Vector<int>;
  // In .cpp:
  template class Vector<int>;
  ```
- When adding support for a new type, register it in both files.
- Mixed-type arithmetic must return `typename std::common_type<T,U>::type` for real operands. When the result is complex, wrap it: `std::complex<typename std::common_type<T,U>::type>`.
- Provide separate overloads for real and complex operands rather than a single unconstrained template; this avoids ambiguity at the cost of a small amount of boilerplate.

## Return Types and `std::optional`

- Prefer return values over output parameters.
- Use `std::optional<T>` for functions that may legitimately produce no result (e.g., the inverse of a potentially singular matrix, finding a pivot):
  ```cpp
  [[nodiscard]] std::optional<Matrix<long double>> inverse(const Matrix<T>&);
  ```
- Use plain aggregate structs (no explicit constructors) for multi-value returns. Apply default member initialization where a sensible default exists:
  ```cpp
  struct Solution {
      bool unique = false;
      std::optional<Vector::Vector<long double>> uniqueSolution;
      // ...
  };
  ```

## Error Handling

- Validate preconditions at public API boundaries using `std::invalid_argument` (or another appropriate `std::exception` subclass):
  ```cpp
  if (other.dim() != data.size())
      throw std::invalid_argument("Cannot add incompatible vectors !");
  ```
- Use `assert()` for internal invariants that must hold by construction and that would indicate a logic bug in the library itself:
  ```cpp
  assert(numRows == c.dim());
  ```
- Never silently ignore an error. Return `std::nullopt` for expected "no result" conditions rather than throwing.

## Const Correctness

- Pass objects by `const&` unless the function needs to modify or take ownership.
- Use `cbegin()`/`cend()` explicitly in const contexts.
- Declare every method that does not mutate state as `const`.

## STL Algorithms and Lambdas

- Prefer STL algorithms (`std::transform`, `std::find_if`, `std::inner_product`, etc.) over raw loops. This expresses intent clearly and reduces off-by-one errors.
- Capture lambda variables explicitly (prefer `[&]` for read-only captures of local context within a small scope, `[=]` when the lambda outlives the local scope).
- Use the IIFE pattern for `const` declarations that require conditional initialization (see **Variables** section above).

## Floating-Point Comparisons

- Never compare floating-point values with `==`. Always compare against a threshold:
  ```cpp
  const long double thresh = 1e-14;
  if (std::abs(value) > thresh) { ... }
  ```
- Define the threshold as a named `const` at file scope (or within an anonymous namespace) so it is reusable and easy to adjust.

## Functions

- Keep functions short and focused. If a function handles more than one distinct concern, split it.
