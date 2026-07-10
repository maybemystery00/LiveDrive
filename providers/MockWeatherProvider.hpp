#pragma once

#include "IWeatherProvider.hpp"

class MockWeatherProvider : public IWeatherProvider
{
public:
    /** @brief Returns fixed weather data regardless of location for testing. */
    WeatherSnapshot Fetch(const Location& location) override;
};
