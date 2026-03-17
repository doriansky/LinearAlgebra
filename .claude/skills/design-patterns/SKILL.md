---
name: design-patterns
description: Use when asked to review or implement design patterns in C++ code.
---

## Observer Pattern

- Ensure that the observer pattern is implemented correctly, with a clear separation of concerns between the subject and observer classes.
- Ensure the observer pattern is implemented in a way that allows for easy addition and removal of observers, without requiring changes to the subject class.
- Ensure that observable holds a list of observers and notifies them of any changes in its state, while observers implement a common interface that allows them to receive notifications from the observable.
- The pointer to the observer should be a **weak pointer** to avoid circular dependencies and memory leaks.

## Factory Pattern

- Use a static factory method (or a free factory function) instead of a public constructor when object creation is complex or the concrete type must be determined at runtime.
- The factory should return the object by value or wrapped in a `std::unique_ptr`; never return a raw pointer.
- Name the factory function clearly to indicate what it creates (e.g., `createSolver`, `makeMatrix`).
- If multiple related types are produced, prefer a single factory with a type-discriminating parameter over several independent factories.

## Adapter Pattern

- Use the Adapter pattern to make an existing class conform to an interface expected by client code, without modifying the existing class.
- Prefer **composition over inheritance**: hold the adaptee as a member (by value or `std::unique_ptr`) rather than inheriting from it.
- The adapter class should expose only the target interface; do not leak adaptee methods into the public API.
- Ensure the adapter is in the same namespace as the target interface it satisfies, not the adaptee's namespace.

## Decorator Pattern

- Use the Decorator pattern to add behaviour to an object dynamically without subclassing.
- All decorators and the concrete component must share a common abstract base class or interface.
- Hold the wrapped component via `std::unique_ptr<Base>` to allow runtime composition and clear ownership.
- Each decorator must forward all interface calls to the wrapped component, augmenting only the behaviour it is responsible for.
- Avoid deep decorator chains (more than 2–3 layers); consider a strategy or policy-based design instead.

## Visitor Pattern

- Use the Visitor pattern to separate an algorithm from the object structure it operates on, particularly when the structure is stable but new operations are added frequently.
- Define a pure `Visitor` interface with one `visit` overload per concrete element type.
- Each concrete element must implement `accept(Visitor&)` and call `visitor.visit(*this)`.
- Prefer `std::variant` + `std::visit` over the classic double-dispatch visitor when the set of element types is closed and known at compile time — it avoids virtual dispatch overhead and is easier to extend with new operations.