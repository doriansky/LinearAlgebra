---
name: implementation
description: Use when asked to implement new C++ functionality or modify existing code.
---

## Prerequisites

- Always refer to the **coding-guidelines** skill before starting an implementation task.
- Always refer to the **documentation** skill to ensure all new public functions, free functions, and structs are documented correctly.
- An **implementation plan** must be provided before starting (either as a file or inline in the conversation). If no plan is present, stop and ask for one.

## Workflow

1. First parse the implementation plan and ensure the entire content is clear.
2. If something is not clear or you need further details, stop and ask for more input.
3. Implement the steps in the order mentioned in the plan.
4. Always implement test cases for the new functionality, ensuring good coverage and following the testing guidelines. Refer to the **test-writer** skill for best practices on writing tests.
5. Always add documentation for member functions and free functions.
6. If the plan consists in multiple stages, stop at the end of each stage and ask for review/feedback.
7. Once the feedback is received you can continue. The feedback can be: "approve", "OK, continue", "implement the next phase" or any other phrase that tells you that so far the work is good and you can continue.
