#include "MockWeatherProvider.hpp"

WeatherSnapshot MockWeatherProvider::Fetch()
{
    WeatherSnapshot weather;

    weather.temperatureC = 22.5f;
    weather.humidity = 68.0f;
    weather.rainIntensity = 0.35f;
    weather.cloudCover = 75.0f;
    weather.windSpeed = 14.2f;
    weather.visibility = 12000.0f;
    weather.pressure = 1013.2f;

    return weather;
}