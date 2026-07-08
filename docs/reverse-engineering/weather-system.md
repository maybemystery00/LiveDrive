# Reverse Engineering Euro Truck Simulator 2's Weather System

## LiveDrive Research Log #1

**Game:** Euro Truck Simulator 2
**Version:** 1.57 x64 (Steam)
**Tools:** Ghidra 12.x, CodeBrowser
**Project:** LiveDrive

---

# Objective

The purpose of this research was to understand how ETS2 handles weather internally in order to build **LiveDrive**, a project that synchronizes in-game weather with real-world weather.

The initial questions were:

* How is weather represented internally?
* Where does `g_set_weather` lead?
* Can weather be controlled directly?
* Is weather profile-based or dynamically simulated?

---

# Starting Point

The investigation began with the developer console command

```
g_set_weather
```

Searching the binary for the string immediately revealed its registration inside the console command table.

```
"g_set_weather"
```

Alongside it were other commands such as

```
g_set_climate
```

showing weather and climate are treated as separate systems.

---

# Command Registration

The string references eventually lead to

```
FUN_140440f00
```

which was renamed

```
Cmd_SetWeather()
```

Decompiler output shows

```cpp
WeatherManager_SetWeather(
    *(undefined8 *)(DAT_143297550 + 0x7f0),
    weatherIndex,
    transitionMode
);
```

This establishes the first part of the pipeline

```
Console

↓

Cmd_SetWeather()

↓

WeatherManager_SetWeather()
```

The console command itself contains almost no weather logic.

It simply parses arguments and forwards them.

---

# WeatherManager_SetWeather

Function

```
FUN_14043cc40
```

renamed

```
WeatherManager_SetWeather()
```

Prototype

```cpp
WeatherManager_SetWeather(
    WeatherManager *manager,
    int weatherIndex,
    int transitionMode
);
```

The function immediately writes

```
manager + 0x3E48
manager + 0x3E4C
```

using

```asm
MOV dword ptr [RCX+3E48], EDX
MOV dword ptr [RCX+3E4C], EDX
```

Decompiler

```cpp
*(int *)(param_1 + 0x3e48) = param_2;
*(int *)(param_1 + 0x3e4c) = param_2;
```

---

# Current Understanding of Offsets

These offsets are **confirmed writes**, but their exact semantics are still under investigation.

| Offset  | Observation                                  | Confidence |
| ------- | -------------------------------------------- | ---------- |
| +0x3E48 | Weather-related state written first          | High       |
| +0x3E4C | Mirrors first write                          | High       |
| +0x4548 | Frequently recalculated after weather change | Medium     |
| +0x454C | Transition state                             | Medium     |
| +0x4550 | Transition timing                            | Medium     |
| +0x45C0 | Blend / interpolation value                  | Medium     |

At this stage only **0x3E48** and **0x3E4C** are directly observed assignments.

The remaining fields are inferred from surrounding logic.

---

# Transition Logic

`WeatherManager_SetWeather()` supports two execution paths.

## Immediate transition

When transition mode equals zero

```cpp
uVar4 = 0;
```

No interpolation is scheduled.

---

## Smooth transition

Otherwise

```cpp
uVar4 = 0x3f800000;
```

which equals

```
1.0f
```

This value is later used together with

```
+0x4550
```

which stores

```
CurrentGameTime + transitionDuration
```

indicating timed interpolation.

---

# Weather Restoration

One of the strongest findings came from

```
FUN_1403eae40
```

renamed

```
ApplyLoadedWeatherState()
```

This routine restores weather after loading.

Relevant section

```cpp
WeatherManager_SetWeather(lVar5,1,1);
```

followed by

```
UpdateSunProfileArrays()

↓

RebuildEnvironment()
```

before returning.

This suggests savegames do **not** rebuild weather manually.

Instead they simply invoke the same WeatherManager used everywhere else.

---

# Rebuild Pipeline

Multiple functions converge to the following execution order

```
WeatherManager_SetWeather()

↓

UpdateSunProfileArrays()

↓

RebuildEnvironment()
```

The rebuild stage refreshes rendering resources.

No evidence was found that rain particles, clouds or fog are generated here.

---

# Cached Weather Property Reader

Function

```
FUN_1400eb650()
```

was initially suspected to contain weather generation.

Instead it behaves as a cache.

Simplified

```cpp
if(cached)
    return cached;

value = ReadProperty();

cache = value;

return value;
```

It does not appear to decide weather.

---

# WeatherManager Call References

Ghidra reports

```
15 references
```

Classification

| Address   | Purpose               |
| --------- | --------------------- |
| 140440fb1 | Console command       |
| 1403eb0e4 | Save/load restoration |
| 1403ed838 | Weather restore       |
| 1403ed86d | Weather restore       |
| 140421c4  | Runtime               |
| 14055d016 | Runtime               |
| 1405b1fae | Runtime               |
| 140b00f07 | Editor                |
| 140c66759 | Runtime               |
| 14142fe72 | Runtime               |
| 141430b18 | Runtime               |
| 14143183f | Runtime               |

Remaining entries belong to

* exception unwind metadata
* PE runtime metadata

and are not executable callers.

---

# Editor Integration

One reference clearly belongs to editor code.

Decompiler

```cpp
WeatherManager_SetWeather(
    param_1[0xfe],
    weatherFromEditor,
    1
);
```

Immediately afterward

```
RebuildEnvironment()
```

is called.

This confirms the editor relies on the exact same runtime weather system.

---

# Weather Is Centralized

An important architectural finding is that every investigated system eventually funnels through

```
WeatherManager_SetWeather()
```

including

* console
* editor
* save loading
* runtime restoration

No alternative weather pipeline has been discovered.

---

# What Has NOT Been Found

Despite tracing the complete weather application path, several important components remain unidentified.

Not yet located

* Rain intensity calculation
* Cloud density calculation
* Fog generation
* Wind simulation
* Thunder probability
* Climate selection algorithm
* Weather profile lookup tables

These almost certainly exist elsewhere.

---

# Current Architecture

The current model looks like

```
Developer Console

        │

        ▼

 Cmd_SetWeather()

        │

        ▼

WeatherManager_SetWeather()

        │
        ├───────────────┐
        │               │
        ▼               ▼

UpdateSunProfileArrays()

        │

        ▼

RebuildEnvironment()

        │

        ▼

Rendering Engine
```

---

# Conclusions

Current evidence indicates that **WeatherManager_SetWeather()** is the central dispatcher responsible for applying weather across ETS2.

The console command, savegame loader, and editor all converge on this function, making it the primary interface for weather changes. The function updates internal WeatherManager state, schedules or performs transitions, refreshes sun profile data, and rebuilds the rendering environment.

However, **this function does not appear to generate weather**. Instead, it applies an already-selected weather state.

The algorithms responsible for deciding **which weather profile to use**, how rain intensity evolves, or how climate regions influence weather remain outside the scope of the functions examined so far.

---

# Next Research Targets

To continue LiveDrive, the highest-value targets are:

1. Reverse engineer **`g_set_climate`** and determine how climate differs from weather.
2. Trace where the values written to **`0x3E48`** and **`0x3E4C`** originate during normal gameplay.
3. Identify the weather profile database (`weather.sii`, binary tables, or compiled structures).
4. Locate the rain renderer and precipitation controller.
5. Map the complete `WeatherManager` structure instead of individual offsets.
6. Determine how the game decides to switch weather naturally during gameplay.

---

I think this version is suitable for GitHub or a research repository. It clearly separates **confirmed findings** from **inferences**, documents the evidence you collected in Ghidra, and avoids overstating conclusions. That's important if you want other reverse engineers to build on your work or verify it independently.
