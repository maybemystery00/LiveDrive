# 🚛 LiveDrive

> Real-world weather synchronization for **Euro Truck Simulator 2** and **American Truck Simulator** using the **Simulation Plugin Framework (SPF)**.

![Status](https://img.shields.io/badge/status-early%20development-orange)
![Language](https://img.shields.io/badge/language-C%2B%2B20-blue)
![Platform](https://img.shields.io/badge/platform-Windows-blue)
![License](https://img.shields.io/badge/license-Apache--2.0-blue)

---

# Overview

LiveDrive is an open-source project that brings real-world weather into Euro Truck Simulator 2 and American Truck Simulator.

Instead of using static weather presets, LiveDrive retrieves live weather information based on either the player's real-world location or the truck's in-game position, interprets that data, and smoothly recreates the conditions inside the game using the upcoming Simulation Plugin Framework (SPF) Weather API.

The project focuses on creating realistic, immersive weather transitions while remaining modular, maintainable, and easy to extend.

---

# Motivation

Weather is one of the most important parts of immersion in a driving simulator.

Current weather systems are limited to predefined weather profiles and manual console commands. Although these provide variety, they cannot reflect the constantly changing conditions of the real world.

LiveDrive aims to bridge that gap by automatically synchronizing the game with live weather services while preserving the natural look and feel of the game's weather system.

---

# Goals

The primary goals of LiveDrive are:

- Synchronize ETS2/ATS weather with real-world weather.
- Support multiple weather providers.
- Support multiple location sources.
- Create smooth, believable weather transitions.
- Remain modular and easily maintainable.
- Integrate natively with the Simulation Plugin Framework (SPF).
- Be fully open source.

---

# Features

## Planned

- Live weather synchronization
- User location mode
- In-game location mode
- Multiple weather providers
- Automatic weather updates
- Smooth weather transitions
- Rain intensity control
- Fog control
- Skybox selection
- Temperature synchronization
- Road wetness synchronization
- Climate synchronization
- Modular architecture
- Extensible plugin system

---

# Current Progress

## Completed

- Project setup
- CMake build system
- Git repository
- GitHub repository
- Weather architecture
- WeatherSnapshot model
- Weather provider interface
- Mock weather provider

## In Progress

- Location system
- Backend architecture
- Documentation

## Planned

- HTTP networking
- Weather provider integration
- JSON parsing
- Weather interpretation
- Transition planner
- Coordinate mapping
- SPF Weather API integration

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

# Location Modes

## User Location

Uses the player's real-world location.

Suitable for users who want the game weather to match their current environment.

Example:

```
Player Location

↓

Berlin

↓

Current Weather

↓

ETS2
```

---

## In-Game Location

Uses the truck's current position inside the game world.

The position is translated into real-world coordinates before requesting weather data.

Example:

```
Truck Position

↓

France

↓

Real Weather

↓

ETS2
```

---

# Planned Weather Pipeline

```
Location Provider

↓

Weather Provider

↓

Weather Snapshot

↓

Interpreter

↓

Transition Planner

↓

SPF Weather API

↓

Game
```

---

# Project Structure

```
LiveDrive
│
├── app/
│
├── core/
│
├── providers/
│
├── planner/
│
├── interpreter/
│
├── output/
│
├── config/
│
├── tests/
│
├── docs/
│
├── README.md
├── CONTRIBUTING.md
├── LICENSE
└── CMakeLists.txt
```

---

# Technology Stack

Core Language

- C++20

Build System

- CMake

Compiler

- GCC (MSYS2 UCRT64)

Networking

- libcurl

JSON

- nlohmann/json

Plugin Framework

- Simulation Plugin Framework (SPF)

Weather Source

- Open-Meteo (initial implementation)

Version Control

- Git

Repository Hosting

- GitHub

---

# Building

## Requirements

- Windows
- MSYS2 (UCRT64)
- CMake
- GCC
- Git

Clone the repository:

```bash
git clone https://github.com/maybemystery00/LiveDrive.git
```

Enter the project:

```bash
cd LiveDrive
```

Configure:

```bash
mkdir build
cd build
cmake ..
```

Build:

```bash
cmake --build .
```

Run:

```bash
./LiveDrive.exe
```

---

# Roadmap

- Project architecture
- Location system
- HTTP backend
- Weather provider implementation
- JSON parsing
- Weather interpretation
- Transition planner
- Coordinate mapping
- SPF integration
- Alpha release
- Beta release
- Version 1.0

A more detailed roadmap can be found in:

```
docs/ROADMAP.md
```

---

# Documentation

Additional documentation is available in the `docs` directory.

- Architecture
- Development Guide
- Roadmap
- Reverse Engineering Research
- Changelog

---

# Reverse Engineering Research

Although LiveDrive primarily relies on the Simulation Plugin Framework, the project also includes research into the internal weather systems of ETS2.

These documents are intended for educational purposes and future experimentation.

Research can be found under:

```
docs/reverse-engineering/
```

---

# Project Status

LiveDrive is currently in active development.

The software is not yet feature complete and should be considered experimental.

Breaking architectural changes may occur until the first stable release.

---

# Contributing

Contributions, suggestions, bug reports, and architectural discussions are always welcome.

Before contributing, please read:

```
CONTRIBUTING.md
```

---

# Acknowledgements

Special thanks to:

- SCS Software for Euro Truck Simulator 2 and American Truck Simulator
- The Simulation Plugin Framework (SPF) developers
- Everyone contributing feedback, testing, and ideas throughout the development process

---

# License

This project is licensed under the GNU General Public License v3.0.

See the LICENSE file for details.
