#pragma once

#include "../core/Location.hpp"
#include "../core/WeatherSnapshot.hpp"

class IWeatherProvider
{
public:
    virtual ~IWeatherProvider() = default;

    /** @brief Fetches weather for the supplied normalized location. */
    virtual WeatherSnapshot Fetch(const Location& location) = 0;
};
