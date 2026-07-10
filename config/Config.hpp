#pragma once

#include <string>

/**
 * @brief Stores the user-configurable settings used by LiveDrive.
 *
 * Future versions will extend this model with API keys, cache settings,
 * debug options, SPF settings, and transition settings.
 */
struct Config
{
    /**
     * @brief Creates a configuration populated with supported default values.
     * @return The default LiveDrive configuration.
     */
    static Config CreateDefault();

    /** Number of seconds between weather updates. */
    int updateInterval;

    /** Logging verbosity: trace, debug, info, warning, or error. */
    std::string logLevel;

    /** Location source: manual, user, or in_game. */
    std::string locationMode;

    /** Manual-location latitude in decimal degrees. */
    double latitude;

    /** Manual-location longitude in decimal degrees. */
    double longitude;

    /** Selected weather provider. Only mock is currently supported. */
    std::string weatherProvider;

    /** Preferred measurement system: metric or imperial. */
    std::string units;
};
