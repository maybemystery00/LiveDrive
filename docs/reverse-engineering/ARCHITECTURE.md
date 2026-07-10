# LiveDrive Architecture

## Overview

LiveDrive is designed as a modular weather synchronization system for Euro Truck Simulator 2 (ETS2) and American Truck Simulator (ATS).

Rather than tightly coupling every part of the application together, LiveDrive separates responsibilities into independent components. Each component performs exactly one task and communicates with the next component through well-defined interfaces.

This architecture makes the project easier to understand, easier to test, easier to maintain, and easier to extend in the future.

---

# Design Principles

LiveDrive follows several core design principles.

## Single Responsibility Principle

Every class should have one responsibility.

Examples:

- A Location Provider only determines where weather should be fetched from.
- A Weather Provider only downloads weather.
- The Interpreter only converts weather into game values.
- The Transition Planner only decides how weather changes over time.

No component should perform multiple unrelated tasks.

---

## Separation of Concerns

Each system is isolated from the others.

Changing one component should require little or no modification to the rest of the project.

For example:

Replacing Open-Meteo with another weather service should not require changes to the transition planner.

Replacing ETS2 with ATS should not require changes to the weather provider.

---

## Modularity

Every subsystem is designed to be replaceable.

Future developers should be able to create their own:

- Weather Providers
- Location Providers
- Output Adapters

without modifying existing code.

---

## Extensibility

Future features should be added by introducing new components instead of modifying existing ones whenever possible.

Examples:

- Add WeatherAPI.com support
- Add Tomorrow.io support
- Add offline weather simulation
- Add custom weather scripting

---

# High-Level Architecture

```
                Configuration
                       │
                       ▼
              Location Provider
                       │
                       ▼
              Weather Provider
                       │
                       ▼
              Weather Snapshot
                       │
                       ▼
           Weather Interpreter
                       │
                       ▼
           Transition Planner
                       │
                       ▼
              SPF Weather API
                       │
                       ▼
                  ETS2 / ATS
```

---

# Project Structure

```
LiveDrive
│
├── app/
├── core/
├── providers/
├── planner/
├── interpreter/
├── output/
├── config/
├── tests/
├── docs/
│
├── README.md
├── CONTRIBUTING.md
├── LICENSE
└── CMakeLists.txt
```

---

# Directory Responsibilities

## app/

Contains the application's entry point.

Responsibilities:

- Start the application
- Initialize systems
- Connect components
- Run the application loop

This directory should contain very little business logic.

---

## core/

Contains project-wide data models.

Examples:

- WeatherSnapshot
- Location
- Shared enums
- Shared utility types

These objects are used throughout the application.

---

## providers/

Responsible for retrieving external information.

Examples:

- OpenMeteoProvider
- UserLocationProvider
- ETS2LocationProvider

Providers never interpret data.

They only retrieve it.

---

## interpreter/

Responsible for converting real-world weather into values suitable for ETS2.

Examples:

Real rain probability

↓

Rain intensity

Cloud cover

↓

Skybox selection

Visibility

↓

Fog density

Temperature

↓

Game temperature

---

## planner/

Responsible for creating believable weather transitions.

Instead of instantly changing weather, this system decides:

- transition duration
- interpolation
- gradual rain changes
- fog progression

---

## output/

Responsible for communicating with external systems.

Initially:

- SPF Weather API

Potential future outputs:

- Debug console
- Logging
- Recording
- Replay

---

## config/

Stores application configuration.

Examples:

Preferred weather provider

Location mode

Refresh interval

API keys

Transition settings

---

## tests/

Contains unit and integration tests.

Examples:

Weather parsing

Coordinate conversion

Interpreter correctness

Transition calculations

---

# Core Data Model

## WeatherSnapshot

WeatherSnapshot represents the current weather in LiveDrive's internal format.

Every weather provider converts its own API response into this common representation.

Example:

```
Open-Meteo JSON

↓

WeatherSnapshot

↓

Interpreter
```

Future providers never interact directly with the interpreter.

They only produce WeatherSnapshot objects.

---

## Location

Location represents where weather should be requested.

Future versions may contain:

- latitude
- longitude
- city
- country
- timezone

The rest of the application should never care how this location was obtained.

---

# Provider System

The Provider layer retrieves information.

There are two categories.

## Location Providers

Responsible for determining location.

Examples:

User Location

Truck Position

Manual Coordinates

Saved Location

---

## Weather Providers

Responsible for downloading weather.

Examples:

Open-Meteo

WeatherAPI

Tomorrow.io

OpenWeatherMap

---

# Processing Pipeline

The complete LiveDrive pipeline is:

```
Determine Location

↓

Download Weather

↓

Convert to WeatherSnapshot

↓

Interpret Weather

↓

Plan Transition

↓

Send Commands to SPF

↓

ETS2 / ATS
```

---

# Weather Pipeline

## Step 1

Determine location.

Possible sources:

- User
- Truck
- Manual

---

## Step 2

Download weather.

The selected Weather Provider communicates with the chosen weather service.

---

## Step 3

Normalize data.

Different APIs use different field names.

Everything is converted into WeatherSnapshot.

---

## Step 4

Interpret weather.

Example:

Real cloud cover

↓

Skybox

Real humidity

↓

Fog intensity

Real precipitation

↓

Rain intensity

---

## Step 5

Transition planning.

Weather should never instantly snap.

The planner creates gradual transitions.

---

## Step 6

Output.

The generated weather state is sent to ETS2 using the Simulation Plugin Framework.

---

# Why Interfaces?

Interfaces allow components to be replaced without changing the rest of the application.

Example:

```
IWeatherProvider

        ▲

 ┌──────┴────────┐

OpenMeteo    WeatherAPI
```

Both providers return the same WeatherSnapshot.

The rest of LiveDrive never needs to know which provider is being used.

---

# Current Development Status

Implemented:

- Project structure
- Build system
- WeatherSnapshot
- Weather Provider interface
- Mock Weather Provider

In Progress:

- Location system

Planned:

- HTTP networking
- Weather services
- JSON parsing
- Interpreter
- Transition planner
- SPF integration

---

# Future Expansion

Potential future features include:

- Historical weather playback
- Route weather forecasting
- Dynamic storm tracking
- Multiple weather providers
- Offline weather cache
- Weather recording and replay
- Community weather profiles

---

# Non-Goals

LiveDrive is not intended to:

- Replace the game's rendering engine
- Replace the game's climate definitions
- Modify game assets
- Depend on fragile memory offsets when stable APIs exist
- Become a general-purpose game modification framework

---

# Architecture Philosophy

The architecture of LiveDrive prioritizes:

- Readability
- Maintainability
- Extensibility
- Testability
- Modularity

Whenever a new feature is added, preference should be given to introducing a new component rather than increasing the responsibility of an existing one.

This philosophy allows the project to remain understandable as it grows and encourages contributions from other developers while keeping the codebase organized.
