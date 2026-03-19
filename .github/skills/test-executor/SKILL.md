---
name: test-executor
description: Use when asked to run existing tests for the codebase using Google Test.
---

## Output Format

The output of the test executor should be a **TestReport** Markdown document that describes the results of the test execution, including the following sections:

| Section | Description |
|---------|-------------|
| **Overview** | A brief description of the test execution task |
| **Execution Details** | The date and time of the test execution, the name/username of the person who initiated the test run, and machine details (hostname, OS, architecture) when available |
| **Test Results** | A detailed list of the test cases that were executed, including the status of each test case (pass/fail) and any relevant error messages or stack traces for failed tests |
| **Summary** | A summary of the overall test results, including the total number of test cases executed, the number of test cases that passed, and the number of test cases that failed |

The test executor should be clear and concise, providing enough detail for a developer to understand the results of the test execution without further clarification.

## Build Configurations

Both **debug** and **release** builds should be executed and the results should be reported separately to ensure that any issues specific to a particular build configuration are identified and addressed.