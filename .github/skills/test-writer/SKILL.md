---
name: test-writer
description: Use when asked to write a test plan or implement new tests for existing C++ code using Google Test.
---

## Test Plan Structure

The test plan consists of a Markdown document that describes the testing plan. It should include the following sections:

| Section | Description |
|---------|-------------|
| **Overview** | A brief description of the testing task |
| **Test Cases** | A list of test cases that need to be implemented to verify the functionality of the codebase |
| **Test Implementation** | A detailed list of steps to implement the test cases, including any necessary setup and teardown procedures |
| **Test Execution** | Instructions on how to execute the tests and interpret the results |

The test plan should be clear and concise, providing enough detail for a developer to implement the tests without further clarification.

## Testing Strategy

- Have in mind the **testing pyramid** approach, which emphasizes the importance of having a balanced mix of unit tests, integration tests, and end-to-end tests to ensure comprehensive test coverage.
- There should be more unit tests than integration tests, and more integration tests than end-to-end tests, to ensure that the testing effort is focused on the most critical areas of the codebase while still providing sufficient coverage for all levels of testing.

## Quality Requirements

- Ensure that the tests are **automated** and can be run easily as part of the development process, ideally integrated into a continuous integration (CI) pipeline.
- Ensure that the tests are designed to be **maintainable and scalable**, with clear naming conventions and well-organized test suites to facilitate easy navigation and understanding of the test cases.
- Ensure that the tests are designed to be **reliable and consistent**, with clear assertions and error handling to ensure that test failures are informative and actionable for developers.

## Coverage

- Both **positive and negative** test cases should be included to ensure that the codebase is thoroughly tested for both expected and unexpected scenarios.

## Google Test Conventions

- Use `TEST_F` with a fixture class for all test suites that share setup logic. Name the fixture after the class or feature being tested (e.g., `MatrixInverseTests`, `MatrixRightLeftInverseTests`).
- Use plain `TEST` only for fully standalone cases with no shared state.
- Test names must be descriptive and encode the scenario: `<Feature>_<Scenario>` (e.g., `Inverse_Strang_Chapter_1_6_Problem_1_a_row_swap`, `RightInverse_2x3_rank_2`).
- Group related tests into a single `.cpp` file named after the fixture (e.g., `MatrixInverseTests.cpp`). Split into multiple files when a suite grows large (e.g., `MatrixInverseTests_HilbertMatrices.cpp`).

## Build and Run

Tests are built with CMake and run via the `LinearAlgebraTests` binary:

```bash
# Build (from repo root)
cmake -S . -B build
cmake --build build --config Debug   # or Release

# Run all tests
./bin/Debug/LinearAlgebraTests.exe

# Run a specific suite or test
./bin/Debug/LinearAlgebraTests.exe --gtest_filter=MatrixInverseTests.*
./bin/Debug/LinearAlgebraTests.exe --gtest_filter=MatrixInverseTests.Inverse_Singular_Mat
```

After writing tests, use the **test-executor** skill to run them and produce a test report.