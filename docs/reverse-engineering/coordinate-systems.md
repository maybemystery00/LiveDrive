# Reverse Engineering Paper 003
# ETS2 World Coordinate System and Community Map Conversion

**Project:** LiveDrive – ETS2/ATS Real Weather System

**Document Version:** 1.0

**Research Date:** July 2026

---

# Objective

Determine the coordinate system used internally by Euro Truck Simulator 2, understand how the community converts those coordinates into map positions, and evaluate whether this information can be used for LiveDrive's future location system.

This paper documents experimentally verified findings only.

---

# Background

One of the major engineering problems for LiveDrive is determining the truck's real-world location.

The planned weather pipeline requires geographical coordinates (latitude and longitude).

```
ETS2 Truck Position
        ↓
Latitude / Longitude
        ↓
Open-Meteo
        ↓
Weather
```

However, ETS2 does not expose latitude and longitude through telemetry.

Instead, it exposes an internal world coordinate system.

Understanding that coordinate system is therefore the first step toward automatic weather synchronization.

---

# Research Sources

The following independent sources were investigated.

## 1. ETS2 Developer Bug Report

The built-in bug report (F11).

This provides the truck's current world coordinates.

Example:

```
;[11/07/2026 14:05:47] (sec-0002+0002);-4702.21;11.7528;9671.37;0.275985;-0.122243
```

---

## 2. ETS2 Coordinate Conversion Tool

Author:

Denilson Figueiredo

Website:

https://denilson.sa.nom.br/ets2-stuff/coords.html

Purpose:

Convert ETS2 world coordinates into map pixel coordinates.

---

## 3. ETS2 Local Radio

Author:

Koen Vanhove

Purpose:

Automatically determine the truck's nearest city.

Used as confirmation that the same coordinate system is used throughout the community.

---

# ETS2 Bug Report Analysis

The F11 bug report outputs:

```
;Timestamp (Sector);X;Y;Z;Rotation;Pitch
```

Example:

```
;[11/07/2026 14:05:47]
(sec-0002+0002)
-4702.21
11.7528
9671.37
0.275985
-0.122243
```

Meaning:

| Field | Description |
|--------|-------------|
| Timestamp | Time bug report was created |
| Sector | Internal map sector |
| X | World X coordinate |
| Y | Height |
| Z | World Z coordinate |
| Rotation | Vehicle heading |
| Pitch | Vehicle pitch |

Only X and Z are required for map positioning.

---

# Experimental Verification

Truck location:

Stuttgart

Bug report:

```
X = -4702.21

Z = 9671.37
```

The coordinates were entered into the public ETS2 Coordinate Converter.

Result:

The marker appeared exactly inside Stuttgart.

This experimentally proves:

✔ Bug report coordinates represent the same world coordinate system used by the ETS2 community.

---

# Coordinate Conversion Source Code

The coordinate conversion tool is completely client-side.

Its JavaScript contains the following functions.

```
calculatePixelCoordinate()
calculateGameCoordinate()
game_coord_to_funbit()
game_coord_to_koenvh1()
```

No server processing occurs.

---

# Core Formula

The conversion is remarkably simple.

```
PixelX = GameX / Scale + OffsetX

PixelY = GameY / Scale + OffsetY
```

This is an affine transformation.

No trigonometric functions.

No Lambert projection.

No Mercator projection.

No geographic conversion.

---

# Europe Conversion

The JavaScript uses:

```
Scale = 7.278

OffsetX = 11367

OffsetY = 9962
```

Therefore

```
PixelX = GameX / 7.278 + 11367

PixelY = GameZ / 7.278 + 9962
```

---

# Verification

Truck Position

```
GameX = -4702.21

GameZ = 9671.37
```

Calculation

```
PixelX

=

-4702.21 / 7.278

+

11367

=

10720.91
```

Calculation

```
PixelY

=

9671.37 / 7.278

+

9962

=

11290.85
```

These values exactly match the converter output.

Therefore the implementation has been experimentally verified.

---

# Koenvh1 Conversion

Koenvh1 uses

```
Scale = 7.278

OffsetX = 13164

OffsetY = 16260
```

The scale is identical.

Only the offsets change.

Reason:

Koenvh1 uses a different map image.

Therefore only the image origin changes.

---

# United Kingdom Handling

The converter contains a special case.

```
if(x < -31812 && y < -5618)
```

Then

```
Scale = 9.69522

OffsetX = 10226

OffsetY = 9826
```

Otherwise

```
Scale = 7.278

OffsetX = 11367

OffsetY = 9962
```

This indicates the UK map image was calibrated separately.

---

# Important Discovery

This conversion is NOT a GPS conversion.

It converts

```
ETS2 World Coordinates

↓

Map Pixels
```

This allows community software to draw the truck on an image of the ETS2 world.

It does NOT compute latitude or longitude.

---

# Relationship to Local Radio

Koen's Local Radio project also uses the same world coordinates.

Its pipeline is

```
Truck Coordinates

↓

Nearest City

↓

Country

↓

Radio Stations
```

Therefore three independent projects use the same coordinate system.

1.

ETS2 Bug Report

↓

World Coordinates

2.

Coordinate Converter

↓

World Coordinates

↓

Map Pixels

3.

Local Radio

↓

World Coordinates

↓

Nearest City

This strongly validates the correctness of the coordinate system.

---

# Relation to LiveDrive

Current understanding:

```
ETS2

↓

World Coordinates (Verified)

↓

???

↓

Latitude / Longitude

↓

Weather API

↓

Weather Snapshot
```

The unknown component is the conversion from world coordinates to geographic coordinates.

---

# Current Status

Verified:

✔ ETS2 exposes stable world coordinates.

✔ Bug report coordinates are correct.

✔ Community tools use the same coordinate system.

✔ Pixel conversion equations are fully understood.

Unknown:

❌ Conversion to latitude.

❌ Conversion to longitude.

❌ Relationship between world coordinates and climate.sii mapping.

---

# Future Work

Investigate:

1.

climate.sii projection equations.

2.

Lambert Conformal Conic projection used by ETS2.

3.

Relationship between climate map coordinates and world coordinates.

4.

Telemetry SDK coordinate output.

5.

Whether SCS performs an internal transformation before applying climate calculations.

---

# Final Conclusion

The ETS2 community has standardized on a single world coordinate system.

Bug reports, telemetry-based utilities, coordinate visualizers, and Local Radio all use the same X/Z coordinate space.

The transformation from world coordinates to map pixels has been fully reverse engineered and experimentally verified.

The remaining engineering challenge for LiveDrive is not locating the truck inside the ETS2 world.

The remaining challenge is accurately transforming those verified world coordinates into real-world latitude and longitude so that live weather services can be queried automatically.
