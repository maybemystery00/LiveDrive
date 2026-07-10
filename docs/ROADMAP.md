# LiveDrive Roadmap

This document outlines the planned development path for LiveDrive.

The roadmap is intended to provide contributors and users with a clear understanding of the project's current state, future direction, and long-term goals.

The order of milestones may change as development progresses.

---

# Project Vision

LiveDrive aims to become a modern, modular, and extensible weather synchronization system for Euro Truck Simulator 2 and American Truck Simulator.

The long-term vision is to create a plugin capable of accurately reproducing real-world weather while preserving the visual style and atmosphere of the original games.

Rather than replacing the game's weather system, LiveDrive enhances it by intelligently controlling the game's native weather parameters.

---

# Development Philosophy

The project follows several important principles:

- Small incremental milestones
- Stable architecture before features
- Extensive documentation
- Modular codebase
- Open source development
- Community collaboration

Every milestone should leave the project in a functional state.

---

# Milestone 1 — Project Foundation

Status: ✅ Completed

Objectives

- Initialize Git repository
- Create GitHub repository
- Configure CMake
- Configure MSYS2 development environment
- Establish folder structure
- Configure build pipeline

Deliverables

- Working build system
- Successful compilation
- Initial executable

---

# Milestone 2 — Core Architecture

Status: ✅ Completed

Objectives

- Design project architecture
- Implement WeatherSnapshot
- Implement weather abstraction
- Create Weather Provider interface
- Implement Mock Weather Provider

Deliverables

- Modular architecture
- Weather abstraction
- Mock weather system

---

# Milestone 3 — Location System

Status: 🚧 In Progress

Objectives

Design a flexible location system capable of supporting multiple sources.

Features

- Location model
- ILocationProvider interface
- Mock Location Provider
- User Location Provider
- ETS2 Location Provider

Deliverables

- Fully abstracted location system

---

# Milestone 4 — Configuration System

Status: Planned

Objectives

Implement application configuration.

Features

- Configuration loader
- Configuration writer
- User preferences
- Weather provider selection
- Location mode selection
- Refresh interval
- Debug settings

Deliverables

- Persistent configuration

---

# Milestone 5 — HTTP Backend

Status: Planned

Objectives

Build the networking layer.

Features

- libcurl integration
- HTTPS requests
- Error handling
- Timeout handling
- Retry mechanism

Deliverables

- Stable HTTP client

---

# Milestone 6 — Weather Providers

Status: Planned

Objectives

Integrate real weather services.

Initial provider

- Open-Meteo

Future providers

- OpenWeatherMap
- WeatherAPI
- Tomorrow.io

Deliverables

- Live weather retrieval

---

# Milestone 7 — JSON Processing

Status: Planned

Objectives

Parse API responses.

Features

- JSON parser
- Validation
- Unit conversion
- Error recovery

Deliverables

- WeatherSnapshot generation

---

# Milestone 8 — Weather Interpreter

Status: Planned

Objectives

Convert meteorological information into ETS2 weather parameters.

Responsibilities

- Rain intensity
- Cloud coverage
- Fog density
- Temperature
- Road wetness
- Skybox selection
- Climate selection

Deliverables

- Game-ready weather state

---

# Milestone 9 — Transition Planner

Status: Planned

Objectives

Generate smooth weather transitions.

Features

- Transition timing
- Interpolation
- Rain progression
- Fog progression
- Storm evolution

Deliverables

- Natural weather changes

---

# Milestone 10 — Coordinate Mapping

Status: Planned

Objectives

Translate ETS2 world coordinates into geographic coordinates.

Research Areas

- Map projections
- Scale conversion
- Country mapping
- City lookup
- Road network alignment

Deliverables

- Accurate in-game weather synchronization

---

# Milestone 11 — SPF Integration

Status: Planned

Objectives

Connect LiveDrive to the Simulation Plugin Framework.

Features

- Weather API
- Climate API
- Skybox control
- Rain control
- Fog control
- Temperature control
- Road wetness control

Deliverables

- Working in-game weather synchronization

---

# Milestone 12 — User Interface

Status: Planned

Objectives

Create an interface for configuring LiveDrive.

Features

- Settings window
- Status information
- Weather preview
- Debug information

Deliverables

- Complete GUI

---

# Milestone 13 — Performance Optimization

Status: Planned

Objectives

Optimize resource usage.

Tasks

- Weather caching
- Efficient HTTP requests
- Reduced memory usage
- Faster updates

Deliverables

- Production-ready performance

---

# Milestone 14 — Testing

Status: Planned

Objectives

Ensure project stability.

Tests

- Unit tests
- Integration tests
- API tests
- Coordinate mapping tests

Deliverables

- Reliable software

---

# Milestone 15 — Public Alpha

Status: Planned

Objectives

First public testing release.

Features

- Live weather
- User location
- In-game location
- Automatic updates
- Documentation

Deliverables

- Alpha release

---

# Milestone 16 — Version 1.0

Status: Planned

Objectives

Stable public release.

Requirements

- Complete documentation
- Stable architecture
- Full SPF integration
- Comprehensive testing
- Reliable weather synchronization

Deliverables

- LiveDrive v1.0

---

# Long-Term Vision

Potential future features include:

## Multiple Weather Services

Support multiple providers with automatic fallback.

---

## Historical Weather

Replay weather from previous days.

---

## Route Forecast

Forecast weather along the planned route.

---

## Dynamic Storm Tracking

Allow storms to move naturally across the game world.

---

## Offline Cache

Continue operating without an internet connection using cached weather.

---

## Custom Weather Profiles

Allow users to create custom weather interpretation rules.

---

## Replay System

Record and replay weather sessions.

---

## Community Extensions

Support additional providers and plugins developed by the community.

---

# Research Roadmap

Alongside implementation, LiveDrive includes a reverse engineering research effort.

Current research areas include:

- Weather Manager
- Climate System
- Coordinate Mapping
- Environment System
- Skybox Selection
- Rain Controller
- Fog System

Research documents are available under:

```
docs/reverse-engineering/
```

These investigations are intended to improve understanding of the game engine and may enable future enhancements beyond the capabilities of the public APIs.

---

# Current Focus

Current development is focused on completing the backend architecture before implementing gameplay features.

Immediate priorities are:

1. Complete the Location System.
2. Implement configuration management.
3. Build the HTTP backend.
4. Integrate the first weather provider.
5. Develop the weather interpretation pipeline.

Only after these components are complete will work begin on full in-game weather synchronization.

---

# Project Status

Current Version

```
v0.1.0
```

Current Stage

```
Architecture & Backend Development
```

The roadmap will continue to evolve as the project grows and new ideas, community feedback, and capabilities of the Simulation Plugin Framework become available.
