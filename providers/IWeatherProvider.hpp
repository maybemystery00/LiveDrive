#pragma once

#include "../core/WeatherSnapshot.hpp"

class IWeatherProvider
{
public:
    virtual ~IWeatherProvider() = default;

    virtual WeatherSnapshot Fetch() = 0;
};