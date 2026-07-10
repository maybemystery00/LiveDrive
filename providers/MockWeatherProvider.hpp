#pragma once

#include "IWeatherProvider.hpp"

class MockWeatherProvider : public IWeatherProvider
{
public:
    WeatherSnapshot Fetch() override;
};