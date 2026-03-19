---
name: implementation
description: Use when asked to implement new C++ functionality or modify existing code.
---

## Prerequisites

- Always refer to the **coding-guidelines** skill before writing any code.
- Always refer to the **documentation** skill to ensure all new public functions, free functions, and structs are documented correctly.
- Refer to the **add-toolbox-function** skill when adding a new free function to MatrixToolbox.
- Refer to the **cmake-module** skill when adding new `.cpp` source or test files — files not registered in `CMakeLists.txt` will silently not link.
- Refer to the **template-instantiation** skill when adding or modifying template functions — missing instantiations cause `LNK2019` linker errors.
- Refer to the **test-writer** skill when writing new tests for the added functionality.
- Refer to the **test-executor** skill to run tests and generate test reports.
- An **implementation plan** must be provided before starting (either as a file or inline in the conversation). If no plan is present, stop and ask for one.

## Workflow

1. **Parse the plan.** Read the implementation plan in full and ensure every step is clear. If something is ambiguous or incomplete, stop and ask for clarification before writing any code.

2. **Study existing patterns.** Before implementing, read the source files most relevant to the task (e.g., similar functions in `MatrixToolbox.cpp`, the class being extended, existing tests for related features). Match the style, naming, and structure of the surrounding code.

3. **Implement with documentation.** Implement the steps in the order specified by the plan. As you write each public declaration in a `.hpp` file, add its Javadoc comment block immediately — do not defer documentation to a later step. Refer to the **documentation** skill for format and tag conventions.

4. **Register new files.** If you created any new `.cpp` files (library sources or test sources), register them in the appropriate `CMakeLists.txt` before attempting to build. Refer to the **cmake-module** skill.

5. **Register template instantiations.** If you added or modified any template function, add the required explicit instantiation lines to the corresponding `*ExplicitTemplateInstantiations.hpp` file. Refer to the **template-instantiation** skill for the exact syntax.

6. **Build.** Build the project and verify it compiles with zero errors and zero warnings (`-Wall -Werror` is active). If the build fails, consult the **build-troubleshooting** skill to diagnose and fix the issue before proceeding.

7. **Write tests.** Implement test cases for the new functionality, ensuring good coverage of both positive and negative scenarios. Refer to the **test-writer** skill for naming conventions and fixture usage.

8. **Execute tests and generate report.** **Invoke the test-executor skill** to run the newly added tests in both Debug and Release configurations and produce the TestReport. This step is mandatory — do not skip it or defer it to the user. If tests fail, fix the implementation and re-invoke the test-executor skill until all tests pass and the report shows zero failures.

9. **Stage checkpoint.** If the plan consists of multiple stages, stop at the end of each stage and ask for review/feedback. Continue only after receiving confirmation (e.g., "approve", "OK, continue", "implement the next phase").
