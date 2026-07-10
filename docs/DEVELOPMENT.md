# LiveDrive Development Guide

This document describes the development workflow, coding standards, architecture philosophy, and contribution guidelines used throughout the LiveDrive project.

Every contributor should read this document before making changes to the codebase.

---

# Purpose

The goal of this guide is to ensure that LiveDrive remains:

- Easy to understand
- Easy to maintain
- Easy to extend
- Easy to review

As the project grows, maintaining consistency becomes more important than writing clever code.

---

# Development Philosophy

LiveDrive follows several core engineering principles.

## Simplicity

Prefer the simplest solution that correctly solves the problem.

Avoid unnecessary abstractions, premature optimization, and overly complex algorithms.

---

## Single Responsibility Principle

Every class should have exactly one responsibility.

Examples:

Good

WeatherProvider

Downloads weather.

Interpreter

Converts weather.

TransitionPlanner

Creates transitions.

Bad

WeatherManager

Downloads weather.

Parses JSON.

Controls ETS2.

Handles configuration.

Logs messages.

One class should never perform unrelated tasks.

---

## Composition Over Inheritance

Favor composition whenever possible.

Instead of large inheritance hierarchies, build systems by combining smaller independent components.

---

## Modularity

Each module should be replaceable.

Changing the weather provider should not require modifications to the transition planner.

Changing the location provider should not require changes to the interpreter.

---

## Readability First

Code is written for humans.

Prioritize readability over cleverness.

---

# Folder Structure

```
LiveDrive

├── app/
├── core/
├── providers/
├── planner/
├── interpreter/
├── output/
├── config/
├── tests/
├── docs/
```

---

# Folder Responsibilities

## app/

Contains application startup.

Only initialization should exist here.

Business logic belongs elsewhere.

---

## core/

Contains shared project data structures.

Examples

WeatherSnapshot

Location

Enums

Shared utilities

---

## providers/

Responsible for retrieving external information.

Never interpret data.

Never modify game state.

---

## interpreter/

Responsible for converting real-world weather into ETS2 weather.

---

## planner/

Responsible for generating smooth transitions.

---

## output/

Responsible for communicating with ETS2 through SPF.

---

## config/

Configuration loading and saving.

---

## tests/

Automated tests.

---

# Naming Conventions

Classes

Use PascalCase.

Example

```
WeatherSnapshot
OpenMeteoProvider
TransitionPlanner
```

---

Methods

Use PascalCase.

Example

```
FetchWeather()

Interpret()

PlanTransition()
```

---

Variables

Use camelCase.

Example

```
rainIntensity

weatherSnapshot

transitionTime
```

---

Constants

Use ALL_CAPS.

Example

```
DEFAULT_UPDATE_INTERVAL

MAX_RAIN_INTENSITY
```

---

Files

Match class names.

Example

```
WeatherSnapshot.hpp

WeatherSnapshot.cpp
```

---

# Header Files

Every header must begin with

```cpp
#pragma once
```

Avoid include guards.

---

# Includes

Prefer local includes first.

Then standard library.

Example

```cpp
#include "WeatherSnapshot.hpp"

#include <string>

#include <vector>
```

---

# Comments

Only explain **why**.

Avoid comments that explain **what** obvious code does.

Bad

```cpp
// Increment counter

counter++;
```

Good

```cpp
// Prevent excessive weather requests by enforcing a minimum interval.

counter++;
```

---

# Formatting

Use consistent indentation.

Indentation

4 spaces.

Maximum line length

120 characters.

Always use braces.

Good

```cpp
if (success)
{
    Update();
}
```

Avoid

```cpp
if (success)
    Update();
```

---

# Error Handling

Every external operation should be checked.

Examples

HTTP requests

JSON parsing

Configuration loading

SPF API calls

Never assume success.

---

# Logging

Every important event should be logged.

Examples

Provider initialized

HTTP request failed

Configuration loaded

Weather updated

Transition started

Do not spam the log.

---

# Configuration

Never hardcode user settings.

Everything configurable should eventually live in the configuration system.

Examples

Refresh interval

Weather provider

Location mode

Transition duration

Units

Debug mode

---

# Interfaces

Whenever multiple implementations are expected, use interfaces.

Examples

```
IWeatherProvider

ILocationProvider
```

Avoid writing application code that depends on a concrete implementation.

---

# Testing Philosophy

Every major system should be testable independently.

Example

Weather Provider

↓

WeatherSnapshot

↓

Interpreter

↓

Transition Planner

Each step should be independently verifiable.

---

# Git Workflow

Main branch

```
main
```

Feature branches

```
feature/location-provider

feature/openmeteo

feature/interpreter
```

Bug fixes

```
fix/http-timeout

fix/json-parser
```

Documentation

```
docs/readme-update
```

---

# Commit Messages

Follow a consistent format.

Examples

```
feat: add WeatherSnapshot model

feat: implement mock location provider

fix: correct JSON parsing

docs: update architecture

refactor: simplify transition planner
```

Avoid

```
update

stuff

fixed

changes
```

---

# Pull Requests

Every pull request should:

- Build successfully
- Follow coding standards
- Include documentation if necessary
- Keep changes focused
- Avoid unrelated modifications

---

# Dependencies

Current dependencies

- C++20
- CMake
- GCC
- MSYS2 UCRT64
- libcurl
- nlohmann/json
- Simulation Plugin Framework (SPF)

Avoid unnecessary third-party libraries.

---

# Performance

LiveDrive is not performance critical.

Prioritize correctness and maintainability over micro-optimizations.

Optimize only after profiling.

---

# Reverse Engineering

Reverse engineering research exists to improve understanding of ETS2's internal systems.

However, LiveDrive should rely on the official SPF APIs whenever equivalent functionality exists.

Research should not become a runtime dependency unless absolutely necessary.

---

# Documentation

Every new module should include documentation.

If architecture changes, update:

- README.md
- ARCHITECTURE.md
- ROADMAP.md

Documentation is considered part of the codebase.

---

# Code Reviews

Before merging any feature, ask:

Does it have one responsibility?

Is it understandable?

Can it be tested?

Can another implementation replace it?

Does it match the architecture?

If the answer to any question is "No", reconsider the implementation.

---

# Development Workflow

The preferred development workflow is:

Plan

↓

Design

↓

Implement

↓

Test

↓

Document

↓

Review

↓

Merge

Architecture should always be designed before implementation begins.

---

# Long-Term Goal

The objective is not simply to create a working weather synchronization plugin.

The objective is to create a clean, extensible, and maintainable software project that can continue evolving over time and serve as a reference implementation for future ETS2 and ATS plugin development.
