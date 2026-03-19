---
name: git-workflow
description: Use when committing changes, creating a feature branch, or opening a pull request in this repository.
---

## Pre-commit gate

All tests must pass before committing. There is no CI — the gate is manual:

```bash
./bin/Debug/LinearAlgebraTests.exe
```

All tests must show `PASSED`. Do not commit with failing or skipped tests.

## Commit style

- Imperative mood, present tense: "Add", "Fix", "Update", not "Added" or "Fixes"
- Subject line ≤ 72 characters
- Match the tone of existing history: `Make project MSVC compatible`, `Added support for complex matrices`, `Added CLAUDE.md`
- No ticket numbers or emoji unless the user requests them

```bash
git commit -m "Add eigenvalue decomposition to MatrixToolbox"
```

## Branching

```bash
git checkout -b feature/<short-description>   # new functionality
git checkout -b fix/<short-description>        # bug fix
```

Branch from `main`. Keep branches focused on a single feature or fix.

## Pull requests

Use `gh pr create` with a Summary + Test plan body:

```bash
gh pr create --title "Add eigenvalue decomposition" --body "$(cat <<'EOF'
## Summary
- Implements `eigenvalues()` in MatrixToolbox for symmetric real matrices
- Uses QR iteration; returns `std::optional<EigenResult>`

## Test plan
- [ ] All existing tests pass
- [ ] `EigenvalueTests.*` passes for 2×2, 3×3, diagonal, and identity matrices
- [ ] Verified no LNK2019 on clean build
EOF
)"
```
