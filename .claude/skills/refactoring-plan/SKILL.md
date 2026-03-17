---
name: refactoring-plan
description: Use when asked to create a refactoring plan for existing C++ code.
---

## Plan Structure

The refactoring plan consists of a Markdown document that describes the refactoring plan, including the following sections:

| Section | Description |
|---------|-------------|
| **Overview** | A brief description of the refactoring task |
| **Requirements** | A list of requirements for the refactoring task |
| **Implementation Steps** | A detailed list of steps to implement the refactoring task |
| **Testing** | A list of tests that need to be implemented to verify the refactoring task |

The refactoring plan should be clear and concise, providing enough detail for a developer to implement the changes without further clarification.

## Specific Rules

- Ensure that the plan will cover the addition of modern C++ features to existing legacy code (move semantics, attributes such as `nodiscard`, `auto` keyword).
- Label raw memory allocations as **high priority** and ensure modern solutions involving smart pointers are recommended.

## General Rules

- Use the **coding-guidelines** skill to ensure that the refactored code adheres to best practices for C++ development.
- Use the **test-writer** skill to plan the tests that verify the refactoring did not break existing behaviour.
- Ensure that all necessary headers are included in the appropriate files.
- Ensure that all dependencies are correctly managed.
- Ensure that all classes and functions are properly encapsulated in their respective modules.
- Ensure the CMakeFiles are written in such a way that all the binaries will be generated in a common output folder.
- Ensure that all source files are included in the appropriate `CMakeLists.txt` files.
- Ensure that any unused code is removed from the codebase.
- Ensure that the code adheres to best practices for C++ development, including proper use of namespaces, memory management, and code organization.
- Ensure that the code is modular and maintainable.
- Ensure that the code is well-documented, with clear comments explaining the purpose of each class and function.
- Ensure that the code is tested thoroughly, with unit tests covering all major functionality.
- Ensure that the code is optimized for performance, with any bottlenecks identified and addressed.
- Ensure that the plan enumerates each implementation step as a self-contained, reviewable unit so progress can be tracked incrementally.
