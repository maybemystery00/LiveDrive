#include "Config.hpp"

Config Config::CreateDefault()
{
    Config config;

    config.updateInterval = 300;
    config.logLevel = "info";
    config.locationMode = "manual";
    config.latitude = 52.5200;
    config.longitude = 13.4050;
    config.weatherProvider = "mock";
    config.units = "metric";

    return config;
}
