#pragma once

#include <string>

/**
 * @brief Describes the geographic location used to request weather data.
 *
 * Location providers normalize their source-specific data into this model so
 * the rest of the application does not depend on how the location was obtained.
 */
struct Location
{
    /** Latitude in decimal degrees. Positive values are north of the equator. */
    double latitude = 0.0;

    /** Longitude in decimal degrees. Positive values are east of the prime meridian. */
    double longitude = 0.0;

    /** Human-readable city or locality name, when available. */
    std::string city;

    /** Human-readable country name, when available. */
    std::string country;

    /** IANA time-zone identifier for the location, when available. */
    std::string timezone;
};
