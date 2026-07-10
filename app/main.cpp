#include "../config/ConfigManager.hpp"
#include "../providers/ManualLocationProvider.hpp"
#include "../providers/MockWeatherProvider.hpp"
#include "../providers/OpenMeteoWeatherProvider.hpp"

#include <filesystem>
#include <iostream>
#include <memory>

namespace
{
    void PrintConfiguration(const Config& config)
    {
        std::cout << "Configuration\n";
        std::cout << "Location Mode     : " << config.locationMode << '\n';
        std::cout << "Latitude          : " << config.latitude << '\n';
        std::cout << "Longitude         : " << config.longitude << '\n';
        std::cout << "Weather Provider  : " << config.weatherProvider << '\n';
        std::cout << "Update Interval   : " << config.updateInterval << " seconds\n";
        std::cout << "Units             : " << config.units << '\n';
        std::cout << "Log Level         : " << config.logLevel << "\n\n";
    }

    std::unique_ptr<ILocationProvider> CreateLocationProvider(const Config& config)
    {
        if (config.locationMode == "manual")
        {
            return std::make_unique<ManualLocationProvider>(config.latitude, config.longitude);
        }

        std::cerr << "Location mode '" << config.locationMode
                  << "' is not implemented. Falling back to manual coordinates.\n";
        return std::make_unique<ManualLocationProvider>(config.latitude, config.longitude);
    }

    WeatherSnapshot FetchWeather(const Config& config, const Location& location, std::string& activeProvider)
    {
        if (config.weatherProvider == "openmeteo")
        {
            OpenMeteoWeatherProvider provider;
            WeatherSnapshot weather = provider.Fetch(location);

            if (provider.IsLastFetchSuccessful())
            {
                activeProvider = "Open-Meteo";
                return weather;
            }

            std::cerr << "Open-Meteo request failed: " << provider.GetLastError()
                      << " Falling back to MockWeatherProvider.\n";
        }
        else if (config.weatherProvider != "mock")
        {
            std::cerr << "Unknown weather provider '" << config.weatherProvider
                      << "'. Falling back to MockWeatherProvider.\n";
        }

        MockWeatherProvider provider;
        activeProvider = "MockWeatherProvider";
        return provider.Fetch(location);
    }
}

int main(int, char* argv[])
{
    const std::filesystem::path executablePath = std::filesystem::absolute(argv[0]);
    const std::filesystem::path configPath = executablePath.parent_path() / "config.json";

    ConfigManager configManager(configPath);
    Config config = configManager.Load();

    std::unique_ptr<ILocationProvider> locationProvider = CreateLocationProvider(config);
    Location location = locationProvider->GetLocation();
    std::string activeProvider;
    WeatherSnapshot weather = FetchWeather(config, location, activeProvider);

    std::cout << "===== LiveDrive =====\n\n";

    PrintConfiguration(config);

    std::cout << "Latitude    : " << location.latitude << '\n';
    std::cout << "Longitude   : " << location.longitude << '\n';
    std::cout << '\n';

    std::cout << "Weather Source\n";
    std::cout << "Provider          : " << activeProvider << "\n\n";

    std::cout << "Temperature : " << weather.temperatureC << " °C\n";
    std::cout << "Humidity    : " << weather.humidity << " %\n";
    std::cout << "Rain        : " << weather.rainIntensity << '\n';
    std::cout << "Cloud Cover : " << weather.cloudCover << " %\n";
    std::cout << "Wind Speed  : " << weather.windSpeed << " km/h\n";
    std::cout << "Visibility  : " << weather.visibility << " m\n";
    std::cout << "Pressure    : " << weather.pressure << " hPa\n";

    return 0;
}
