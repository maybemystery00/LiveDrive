#include <iostream>

#include "../providers/MockWeatherProvider.hpp"

int main()
{
    MockWeatherProvider provider;

    WeatherSnapshot weather = provider.Fetch();

    std::cout << "===== LiveDrive =====\n\n";

    std::cout << "Temperature : " << weather.temperatureC << " °C\n";
    std::cout << "Humidity    : " << weather.humidity << " %\n";
    std::cout << "Rain        : " << weather.rainIntensity << '\n';
    std::cout << "Cloud Cover : " << weather.cloudCover << " %\n";
    std::cout << "Wind Speed  : " << weather.windSpeed << " km/h\n";
    std::cout << "Visibility  : " << weather.visibility << " m\n";
    std::cout << "Pressure    : " << weather.pressure << " hPa\n";

    return 0;
}