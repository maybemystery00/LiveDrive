# Contributing to LiveDrive

First of all, thank you for your interest in contributing to LiveDrive!

Whether you're fixing a bug, improving documentation, implementing a feature, or simply sharing ideas, your contribution is greatly appreciated.

LiveDrive is an open-source project built with maintainability, readability, and collaboration in mind.

---

# Before You Start

Please read the following documents before contributing:

- README.md
- docs/ARCHITECTURE.md
- docs/DEVELOPMENT.md
- docs/ROADMAP.md

Understanding the project's architecture before writing code helps keep the codebase clean and consistent.

---

# Ways to Contribute

There are many ways to contribute to LiveDrive.

Examples include:

- Reporting bugs
- Suggesting new features
- Improving documentation
- Refactoring code
- Adding tests
- Reviewing pull requests
- Researching ETS2/ATS systems
- Improving performance

Every contribution is valuable.

---

# Development Setup

Requirements:

- Windows
- MSYS2 (UCRT64)
- GCC
- CMake
- Git

Clone the repository:

```bash
git clone https://github.com/maybemystery00/LiveDrive.git
```

Enter the project:

```bash
cd LiveDrive
```

Create the build directory:

```bash
mkdir build
cd build
```

Configure:

```bash
cmake ..
```

Build:

```bash
cmake --build .
```

---

# Branch Strategy

Never work directly on the main branch.

Create a feature branch.

Example:

```bash
git checkout -b feature/location-provider
```

Examples:

```
feature/open-meteo

feature/interpreter

feature/spf-weather

feature/config

fix/http-timeout

docs/readme
```

---

# Commit Messages

Use clear commit messages.

Examples:

```
feat: implement Location model

feat: add Open-Meteo provider

fix: prevent invalid weather parsing

docs: update architecture

refactor: simplify transition planner
```

Avoid messages such as:

```
update

changes

stuff

fixed

test
```

---

# Coding Standards

Please follow the coding standards defined in:

```
docs/DEVELOPMENT.md
```

Important rules include:

- One responsibility per class
- Small focused commits
- Readable code
- Document public APIs
- No unnecessary dependencies

---

# Pull Requests

Before opening a Pull Request:

- Ensure the project builds successfully.
- Keep changes focused on a single feature or fix.
- Update documentation if required.
- Remove debugging code.
- Ensure formatting is consistent.

Describe:

- What changed
- Why it changed
- Any limitations
- Future work (if applicable)

---

# Issues

When reporting a bug, include:

- Operating system
- Compiler version
- Steps to reproduce
- Expected behavior
- Actual behavior
- Screenshots (if applicable)

Feature requests should explain:

- The problem
- The proposed solution
- Alternative approaches
- Why the feature would benefit the project

---

# Architecture

Please avoid introducing architectural changes without discussion.

Major design decisions should be proposed through a GitHub Issue before implementation.

Architecture consistency is more important than adding features quickly.

---

# Reverse Engineering

LiveDrive includes research into the internal systems of ETS2.

Reverse engineering documents should:

- Clearly separate confirmed findings from hypotheses.
- Include the game version.
- Document tools used.
- Explain methodology.
- Avoid speculation without evidence.

---

# Documentation

Documentation is considered part of the project.

Whenever a feature changes the architecture or workflow, update the relevant documentation.

Documentation should remain synchronized with the codebase.

---

# Code Review Philosophy

Code reviews focus on:

- Readability
- Simplicity
- Maintainability
- Correctness
- Architectural consistency

Constructive feedback is encouraged.

The goal is to improve the project, not criticize contributors.

---

# Community

Please be respectful.

Questions are welcome.

Suggestions are encouraged.

Constructive discussions often lead to better solutions.

LiveDrive is intended to be a collaborative project where contributors can learn, experiment, and build together.

---

# License

By contributing to LiveDrive, you agree that your contributions will be distributed under the project's license.
