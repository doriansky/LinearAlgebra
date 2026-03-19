---
name: code-review
description: Use when asked to review C++ code after an implementation task. Verifies that the implementation matches the plan and follows coding and documentation guidelines.
---

## Prerequisites

- In order to perform a code review, refer to the **implementation plan** which must be explicitly provided (either as a file or inline in the conversation). The goal is to verify that the implementation followed the plan. Ask for the plan if it is not provided.
- Refer to the **coding-guidelines** skill to check if the coding guidelines were followed.
- Refer to the **documentation** skill to check if all public API functions, free functions, and structs are documented correctly.

## Output Format

The result of the code review should be a document where the findings are enumerated in the order of their importance/relevance (critical findings first, minor comments last).

For each finding, include the following:

| Section | Description |
|---------|-------------|
| **Location** | The file and line(s) the finding refers to |
| **Description** | Why this is a problem, what rule is not followed, and potential consequences |
| **Suggestion** | A potential fix |
