# ETS2 Coordinate System Analysis
**Document Version:** 1.0  
**Project:** LiveDrive    
**Status:** Research (Partially Verified)

---

# Purpose

This document analyzes how Euro Truck Simulator 2 stores and converts map coordinates into geographic coordinates using the information available inside:

```

def/climate.sii

```

The goal is to understand how ETS2 maps the truck's in-game position to real-world latitude and longitude.

This research is the foundation for the future LiveDrive `ETS2LocationProvider`, which will automatically determine the player's real-world location and request weather data from Open-Meteo.

---

# Source

File analyzed:

```

def/climate.sii

```

Relevant section:

```
latitude  = map_origin[0] + (map_z - map_offset[0]) * map_factor[0]

longitude = map_origin[1] + (map_x - map_offset[1]) * map_factor[1]

If advanced map projection is used (eg lambert)
projection is applied on coordinates accordingly.
```

This comment is written by the SCS developers and therefore represents the intended coordinate conversion algorithm.

---

# What is climate.sii?

`climate.sii` is **not executable code**.

It is an SII (SCS Structured Information) file containing configuration data that is loaded by the game engine during startup.

Internally, the engine likely performs something similar to:

```cpp
LoadClimateProfiles();
```

Each `climate_profile` entry becomes an object in memory.

Example:

```
climate_profile : climate.default
{
    ...
}
```

Conceptually:

```cpp
ClimateProfile defaultClimate;
```

The values inside the block become member variables of that object.

---

# Coordinate Conversion

The file provides the exact mathematical relationship between game coordinates and geographic coordinates.

## Latitude

```
latitude =
map_origin[0]
+
(map_z - map_offset[0])
×
map_factor[0]
```

Using the default values:

```
latitude =
50
+
(map_z - 4150)
×
(-0.000171570875)
```

---

## Longitude

```
longitude =
map_origin[1]
+
(map_x - map_offset[1])
×
map_factor[1]
```

Substituting values:

```
longitude =
15
+
(map_x - 16660)
×
0.0001729241463
```

---

# Meaning of Every Parameter

## map_origin

```
map_origin: (50,15)
```

Confirmed:

Represents the geographic reference point used by the conversion.

```
Latitude Reference = 50°

Longitude Reference = 15°
```

Every coordinate is calculated relative to this point.

---

## map_offset

```
map_offset:
(
16660,
4150
)
```

Confirmed:

Represents the origin of the game world's coordinate system.

Instead of beginning at (0,0), ETS2 begins coordinate calculations from this internal reference.

Conceptually:

```
Game World

0 ----------------------------- 30000

             ^
             |
        map_offset
```

---

## map_factor

```
map_factor:

(-1.71570875e-4,
 1.729241463e-4)
```

Confirmed:

Scale factor converting game distance into geographic degrees.

Interpretation:

```
1 game unit

↓

approximately

0.00017°
```

Latitude uses a negative scale.

Longitude uses a positive scale.

Meaning:

Increasing Z decreases latitude.

Increasing X increases longitude.

---

## map_projection

```
map_projection:
lambert_conic
```

Confirmed:

The game applies a Lambert Conformal Conic projection.

The comment explicitly states:

```
If advanced map projection is used
projection is applied accordingly.
```

Therefore the previous linear conversion is not necessarily the final coordinate.

Pipeline:

```
Game Coordinates

↓

Linear Conversion

↓

Lambert Projection

↓

Final Latitude/Longitude
```

---

## standard_parallel_1

```
37°
```

## standard_parallel_2

```
65°
```

Confirmed:

Parameters required by the Lambert Conformal Conic projection.

These determine where the projection cone intersects the Earth.

No evidence currently suggests these change during gameplay.

---

# Worked Example

Suppose telemetry reports

```
X = 17000

Z = 4500
```

Latitude

```
50

+

(4500-4150)

×

(-0.000171570875)

=

49.93995°
```

Longitude

```
15

+

(17000-16660)

×

0.0001729241463

=

15.05879°
```

These values are then passed through the Lambert projection.

---

# Coordinate Flow

Current understanding:

```
Truck Position

(X,Z)

↓

Subtract map_offset

↓

Multiply by map_factor

↓

Add map_origin

↓

Lambert Conformal Conic Projection

↓

Latitude / Longitude
```

---

# Climate Profiles

The file defines multiple climate profiles.

Examples:

```
default

cold

arid

desert
```

Each profile shares the same coordinate system.

Only weather behaviour changes.

Therefore coordinate conversion is independent of climate.

---

# copy Keyword

Example:

```
copy:
default
```

Confirmed behaviour:

Inheritance of configuration values.

Equivalent concept:

```cpp
ClimateProfile desert = default;
```

Then selected fields are overwritten.

Example:

```
temperature

weights

bad_weather_factor
```

---

# Weather Probability

Different climates specify different values.

Examples:

```
Default

0.07
```

```
Arid

0.03
```

```
Desert

0.01
```

Hypothesis:

`bad_weather_factor` influences the probability of selecting bad weather.

This has not yet been confirmed by engine code.

---

# Wetting

```
wetting_factor
```

Hypothesis:

Controls how quickly road surfaces become wet.

---

# Drying

```
drying_factor
```

Hypothesis:

Controls how quickly road surfaces dry after rain.

---

# weights[]

Multiple climates define:

```
weights: 23
```

followed by

```
weights[]
```

Hypothesis:

These are weighted probabilities for weather presets, skyboxes, or weather events.

Further reverse engineering is required.

---

# Relation to LiveDrive

Current LiveDrive

```
Manual Coordinates

↓

Open-Meteo

↓

WeatherSnapshot
```

Future LiveDrive

```
Truck Position

↓

Coordinate Conversion

↓

Latitude/Longitude

↓

Open-Meteo

↓

WeatherSnapshot
```

The conversion described in `climate.sii` forms the basis of the future `ETS2LocationProvider`.

---

# Verified Facts

✓ ETS2 stores coordinate conversion constants inside `climate.sii`.

✓ Coordinate conversion begins with a linear transformation.

✓ Lambert Conformal Conic projection is used.

✓ All climate profiles use the same coordinate system.

✓ Climate profiles inherit from one another using `copy`.

---

# Hypotheses

The following items require verification.

- Exact implementation of Lambert projection.
- Meaning of `weights[]`.
- Meaning of `bad_weather_factor`.
- Meaning of `wetting_factor`.
- Meaning of `drying_factor`.
- Whether linear conversion already produces sufficiently accurate coordinates for weather APIs.

---

# Future Experiments

1. Obtain live truck coordinates using telemetry.

2. Apply the published conversion formula.

3. Compare computed coordinates against known city locations.

4. Measure conversion error.

5. Determine whether Lambert projection is necessary for accurate weather lookup.

6. Compare results across DLC maps.

---

# Conclusion

The `climate.sii` file provides the first confirmed description of ETS2's coordinate mapping.

Rather than storing latitude and longitude directly, ETS2 converts internal world coordinates using a linear transformation followed by a Lambert Conformal Conic projection.

This discovery establishes the mathematical foundation for automatic location detection inside LiveDrive and removes the need for manually configured coordinates once telemetry integration is implemented.
