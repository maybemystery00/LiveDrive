# LiveDrive Project Principles

## Purpose

This document defines the engineering principles that guide the development of LiveDrive.

Unlike the architecture documentation, which explains how the software is structured, this document explains *why* certain decisions are made.

Every new feature, refactor, and contribution should align with these principles.

---

# Vision

LiveDrive exists to bring realistic, real-world weather synchronization to Euro Truck Simulator 2 and American Truck Simulator while maintaining a clean, modular, and maintainable software architecture.

The project is intended to be a long-term open-source effort rather than a quick proof of concept.

---

# Core Philosophy

LiveDrive is built around one simple idea:

> Good architecture outlives individual features.

Features will change.

Weather providers will change.

The Simulation Plugin Framework will evolve.

The architecture should remain stable.

---

# Principles

## 1. Architecture Before Implementation

No feature should be implemented before its place in the architecture is understood.

Before writing code, ask:

- Where does this belong?
- What is its responsibility?
- Does it fit the existing architecture?

Avoid adding functionality simply because it works.

---

## 2. Single Responsibility

Every class should perform one task.

Examples:

Weather Provider

Downloads weather.

Interpreter

Converts weather.

Transition Planner

Plans weather transitions.

Output Adapter

Communicates with the game.

If a class starts performing multiple unrelated tasks, it should be split.

---

## 3. Separation of Concerns

Every subsystem should operate independently.

Examples:

Changing the weather provider should not affect the transition planner.

Changing the location provider should not require modifications to the interpreter.

Changing the output system should not affect networking.

---

## 4. Modularity

Every component should be replaceable.

Future developers should be able to implement their own:

- Weather Providers
- Location Providers
- Output Adapters
- Configuration Systems

without modifying unrelated code.

---

## 5. Interfaces First

Whenever multiple implementations are expected, use interfaces.

Examples:

IWeatherProvider

ILocationProvider

Future implementations should integrate without requiring changes elsewhere.

---

## 6. Internal Data Model

LiveDrive should always convert external data into its own internal representation.

Example:

Open-Meteo JSON

↓

WeatherSnapshot

↓

Interpreter

The rest of the project should never depend directly on third-party API formats.

---

## 7. Readability Over Cleverness

Code should be understandable.

Avoid unnecessary complexity.

Prefer code that another developer can understand in five minutes over code that is technically impressive but difficult to maintain.

---

## 8. Documentation Is Part of the Project

Documentation should evolve alongside the code.

Whenever architecture changes, update:

- README
- Architecture Guide
- Roadmap
- Development Guide

Documentation is not optional.

---

## 9. Small, Reviewable Changes

Large commits are discouraged.

Each commit should represent one logical improvement.

Good examples:

```
feat: implement Location model

feat: add Open-Meteo provider

docs: update architecture

fix: prevent invalid JSON parsing
```

---

## 10. Stability Over Speed

It is better to implement a feature correctly than quickly.

Avoid rushing implementations that compromise architecture.

---

# Reverse Engineering

Reverse engineering is an important part of understanding ETS2 and ATS.

However, reverse engineering is **research**, not the foundation of LiveDrive.

Whenever the Simulation Plugin Framework provides an official API for a feature, that API should be preferred over undocumented internal game functions.

Reverse engineering should be used only when:

- no supported API exists,
- deeper understanding is required,
- or new capabilities are being researched.

---

# External Dependencies

Every dependency should have a clear purpose.

Avoid introducing libraries that provide little benefit.

Before adding a dependency, ask:

- Does the standard library already solve this?
- Is the dependency actively maintained?
- Does it significantly improve the project?

---

# Error Handling

External systems should never be trusted.

Always validate:

- HTTP responses
- JSON data
- Configuration files
- User input
- Game API calls

Assume failure is possible.

---

# Testing

Every major subsystem should be independently testable.

Networking should be testable without the game.

The interpreter should be testable without networking.

The transition planner should be testable without ETS2.

Testing improves confidence and simplifies future refactoring.

---

# Open Source

LiveDrive welcomes contributions from the community.

Contributors are encouraged to:

- improve documentation,
- fix bugs,
- suggest architectural improvements,
- implement new providers,
- expand testing.

Constructive discussion is encouraged.

---

# Long-Term Maintainability

The project should remain understandable years after its creation.

Future contributors should be able to understand the architecture without reading every line of source code.

Maintaining clarity is more important than minimizing the number of files.

---

# Decision Process

When faced with multiple possible solutions, prefer the one that best satisfies the following priorities:

1. Correctness
2. Maintainability
3. Readability
4. Extensibility
5. Performance

Performance optimization should only occur after profiling demonstrates a genuine need.

---

# Relationship with the Simulation Plugin Framework

LiveDrive is designed to integrate closely with the Simulation Plugin Framework (SPF).

SPF provides stable interfaces for interacting with ETS2 and ATS.

LiveDrive focuses on:

- obtaining weather,
- interpreting weather,
- planning transitions,

while SPF is responsible for applying those changes to the game.

This separation allows both projects to evolve independently.

---

# Future Vision

The long-term goal is not simply to synchronize weather.

LiveDrive aims to become a reference implementation demonstrating how modern, modular software architecture can be applied to ETS2 and ATS plugin development.

The project should serve as:

- a useful plugin,
- a learning resource,
- and an example of clean software engineering practices.

---

# Final Principle

> Build software that is easy to understand, easy to extend, and enjoyable to maintain.

Every architectural decision should move the project closer to that goal.
