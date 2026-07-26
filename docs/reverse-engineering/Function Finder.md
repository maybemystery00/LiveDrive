# Function Finder

> **Status:** ❌ Abandoned
>
> **Outcome:** No universal mathematical transformation found.
>
> **Final Dataset:** 267 verified cities

---

# Objective

The goal of this project was to reverse engineer the mathematical relationship between real-world geographic coordinates and **Euro Truck Simulator 2 / American Truck Simulator** world coordinates.

The ideal result would have been a universal function such as:

```text
GameX = f(Latitude, Longitude)

GameZ = g(Latitude, Longitude)
```

or

```text
GameX = f(MercatorX, MercatorY)

GameZ = g(MercatorX, MercatorY)
```

This would allow any real-world location to be converted directly into in-game coordinates.

---

# Initial Dataset

The project started with **329 cities**.

Each record contained:

- City
- Latitude
- Longitude
- Mercator X
- Mercator Y
- Game X
- Game Z

The Game X/Z values were extracted from the game's internal `goto` teleport coordinates using an open-source GitHub project.

These coordinates were treated as ground truth.

---

# Dataset Validation

A custom validator was developed to inspect the dataset.

It checked for:

- Blank rows
- Missing cities
- Duplicate cities
- Duplicate coordinates
- Invalid latitude/longitude
- Europe boundary
- Mercator correctness
- Duplicate Mercator coordinates
- Duplicate Game coordinates
- Precision problems
- Hidden characters
- Leading/trailing spaces

Initial score:

```text
79 / 100
```

---

# Data Cleaning

Several cities had completely incorrect coordinates.

Affected entries:

```text
bado
birsay
cherb
douglas
havre
nikel
ramsey
reydar
trinity
```

Many pointed to North America, Indonesia, or Africa instead of Europe.

---

# Manual Verification

Each incorrect city was manually verified.

| Dataset Name | Correct Location |
|--------------|------------------|
| bado | Bad Oeynhausen, Germany |
| birsay | Birsay, Scotland |
| cherb | Cherbourg, France |
| douglas | Douglas, Isle of Man |
| havre | Le Havre, France |
| nikel | Nikel, Russia |
| ramsey | Ramsey, Isle of Man |
| reydar | Reyðarfjörður, Iceland |

Mercator coordinates were recalculated using the standard Web Mercator projection (EPSG:3857).

---

# Removing Duplicate Game Coordinates

A major issue appeared during validation.

Many unrelated cities shared identical Game X/Z coordinates.

Examples:

```text
Genova ↔ Gizycko
Leipzig ↔ Lellinge
Pecs ↔ Pello
Southampton ↔ Stargard
```

These entries could not all represent real in-game locations.

All duplicate rows were removed.

Dataset size:

```text
329

↓

267 verified cities
```

---

# Final Dataset Quality

| Metric | Result |
|--------|--------|
| Rows | 267 |
| Missing Coordinates | 0 |
| Duplicate Cities | 0 |
| Duplicate Mercator | 0 |
| Duplicate Game Coordinates | 0 |
| Europe Boundary | ✅ |
| Dataset Health | **99 / 100** |

---

# Experiments

## Linear Regression

Model:

```text
Game = A × Mercator + B
```

Result:

```text
RMSE ≈ 8,000
```

This became the baseline.

---

## Affine Transformation

Model:

```text
GameX = aMx + bMy + c

GameZ = dMx + eMy + f
```

Result:

```text
RMSE ≈ 12,000
```

---

## Polynomial Regression

Tested:

- Degree 2
- Degree 3
- Degree 4

Results:

| Model | RMSE |
|-------|------|
| Degree 2 | ~18k |
| Degree 3 | ~36k |
| Degree 4 | ~62k |

Higher-order polynomials overfit badly.

---

# Correlation Analysis

Pearson correlations:

| Relationship | Correlation |
|--------------|------------:|
| Mercator X → Game X | 0.964 |
| Mercator Y → Game Z | -0.977 |
| Mercator X → Game Z | 0.075 |
| Mercator Y → Game X | 0.061 |

This showed that:

- Game X primarily depends on Mercator X.
- Game Z primarily depends on Mercator Y.

However, regional distortions remained.

---

# Residual Analysis

Residual plots showed smooth regional deviations rather than random noise.

This suggested that the transformation might contain local corrections.

---

# Residual Surface Interpolation

Pipeline:

```text
Mercator

↓

Linear Model

↓

Residual

↓

Interpolation

↓

Correction

↓

Final Prediction
```

Training RMSE:

```text
≈ 1,900
```

---

# PCHIP Interpolation

Training:

```text
RMSE ≈ 0
```

Initially appeared perfect.

---

# Random Cross Validation

Cities were randomly removed.

Average prediction error:

```text
RMSE ≈ 15,000
```

Conclusion:

PCHIP simply memorized the dataset.

---

# Clough-Tocher Residual Surface

Training:

```text
RMSE ≈ 0
```

Again appeared perfect.

---

# Leave-One-Out Cross Validation

Each city was removed individually.

The remaining 266 cities were used to predict the missing city.

Results:

```text
RMSE ≈ 89,000

Maximum Error ≈ 1.38 million units
```

This completely invalidated the interpolation approach.

---

# Machine Learning Tournament

Models tested:

- Linear Regression
- Polynomial Regression
- Decision Tree
- Random Forest
- Extra Trees
- Gradient Boosting
- KNN
- Support Vector Regression
- Multi-layer Perceptron

## Results

| Model | RMSE |
|------|------:|
| 🥇 Linear Regression | ~8,035 |
| KNN | ~9,615 |
| Extra Trees | ~12,206 |
| Random Forest | ~12,930 |
| Gradient Boosting | ~12,996 |
| Decision Tree | ~17,556 |
| Polynomial Degree 2 | ~18,150 |
| MLP | ~33,675 |
| SVR | ~40,045 |
| Polynomial Degree 4 | ~62,142 |

Surprisingly, the simplest model performed the best.

---

# Heatmap Analysis

Residual heatmaps showed clear geographical clustering.

This suggested:

```text
Global Transformation

+

Regional Distortion
```

instead of one continuous mathematical equation.

---

# Sector Discovery

Teleport entries contained identifiers such as:

```text
(sec+0010-0016)

(sec-0012+0003)

(sec+0005-0001)
```

This led to a final hypothesis:

```text
Latitude

↓

Mercator

↓

Determine Sector

↓

Sector-specific Transformation

↓

Game Coordinates
```

This hypothesis was never fully explored.

---

# Why the Project Was Abandoned

Three explanations remain plausible:

1. Cities are manually positioned by the map editor.
2. The world is divided into sectors with different transformations.
3. Hidden variables (sector offsets, DLC adjustments, editor corrections) influence placement.

No evidence supported the existence of a single global mathematical transformation.

---

# Achievements

- ✅ Built a comprehensive dataset validator.
- ✅ Verified every incorrect coordinate manually.
- ✅ Produced a 99/100 quality dataset.
- ✅ Removed invalid and duplicate records.
- ✅ Tested multiple regression models.
- ✅ Evaluated interpolation techniques.
- ✅ Compared modern machine learning algorithms.
- ✅ Used proper cross-validation instead of relying on training accuracy.
- ✅ Demonstrated that near-zero training error does **not** imply predictive power.

---

# Final Conclusion

Despite extensive experimentation—including linear regression, affine transformations, polynomial regression, spline interpolation, residual correction fields, and multiple machine learning models—no universal mathematical mapping between real-world coordinates and ETS2 game coordinates was discovered.

The cleaned dataset of **267 verified cities** consistently showed that interpolation methods could perfectly fit known cities while failing dramatically on unseen locations.

The best-performing predictive model remained a simple **Linear Regression** with an RMSE of approximately **8,000 game units**.

The evidence strongly suggests that ETS2's map is **not generated by a single mathematical function**, but instead relies on **manual map editing and/or sector-specific transformations**.

Accordingly, the project has been archived as a documented negative result.
