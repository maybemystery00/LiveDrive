#include "ConfigManager.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

namespace
{
    constexpr int DEFAULT_UPDATE_INTERVAL = 300;
    constexpr int MIN_UPDATE_INTERVAL = 1;
    constexpr int MAX_UPDATE_INTERVAL = 86400;
    constexpr double DEFAULT_LATITUDE = 52.5200;
    constexpr double DEFAULT_LONGITUDE = 13.4050;
    constexpr double MIN_LATITUDE = -90.0;
    constexpr double MAX_LATITUDE = 90.0;
    constexpr double MIN_LONGITUDE = -180.0;
    constexpr double MAX_LONGITUDE = 180.0;

    void LogConfigurationWarning(const std::string& message)
    {
        std::cerr << "Configuration warning: " << message << '\n';
    }

    bool IsAllowedValue(const std::string& value, const std::vector<std::string>& allowedValues)
    {
        for (const std::string& allowedValue : allowedValues)
        {
            if (value == allowedValue)
            {
                return true;
            }
        }

        return false;
    }

    std::string ReadStringValue(
        const nlohmann::json& json,
        const char* name,
        const std::string& defaultValue,
        const std::vector<std::string>& allowedValues)
    {
        if (!json.contains(name))
        {
            LogConfigurationWarning(std::string("Missing ") + name + "; using default value.");
            return defaultValue;
        }

        const nlohmann::json& value = json.at(name);

        if (!value.is_string())
        {
            LogConfigurationWarning(std::string("Invalid ") + name + "; using default value.");
            return defaultValue;
        }

        const std::string stringValue = value.get<std::string>();

        if (!IsAllowedValue(stringValue, allowedValues))
        {
            LogConfigurationWarning(std::string("Unsupported ") + name + "; using default value.");
            return defaultValue;
        }

        return stringValue;
    }

    double ReadCoordinate(
        const nlohmann::json& json,
        const char* name,
        double defaultValue,
        double minimum,
        double maximum)
    {
        if (!json.contains(name))
        {
            LogConfigurationWarning(std::string("Missing ") + name + "; using default value.");
            return defaultValue;
        }

        const nlohmann::json& value = json.at(name);

        if (!value.is_number())
        {
            LogConfigurationWarning(std::string("Invalid ") + name + "; using default value.");
            return defaultValue;
        }

        const double coordinate = value.get<double>();

        if (!std::isfinite(coordinate) || coordinate < minimum || coordinate > maximum)
        {
            LogConfigurationWarning(std::string("Out-of-range ") + name + "; using default value.");
            return defaultValue;
        }

        return coordinate;
    }

    int ReadUpdateInterval(const nlohmann::json& json)
    {
        if (!json.contains("updateInterval"))
        {
            LogConfigurationWarning("Missing updateInterval; using default value.");
            return DEFAULT_UPDATE_INTERVAL;
        }

        const nlohmann::json& value = json.at("updateInterval");

        if (!value.is_number_integer())
        {
            LogConfigurationWarning("Invalid updateInterval; using default value.");
            return DEFAULT_UPDATE_INTERVAL;
        }

        const int updateInterval = value.get<int>();

        if (updateInterval < MIN_UPDATE_INTERVAL || updateInterval > MAX_UPDATE_INTERVAL)
        {
            LogConfigurationWarning("Out-of-range updateInterval; using default value.");
            return DEFAULT_UPDATE_INTERVAL;
        }

        return updateInterval;
    }

    nlohmann::json SerializeConfig(const Config& config)
    {
        return {
            {"locationMode", config.locationMode},
            {"latitude", config.latitude},
            {"longitude", config.longitude},
            {"weatherProvider", config.weatherProvider},
            {"updateInterval", config.updateInterval},
            {"units", config.units},
            {"logLevel", config.logLevel}
        };
    }
}

ConfigManager::ConfigManager(std::filesystem::path configPath)
    : configPath(std::move(configPath))
{
}

Config ConfigManager::Load() const
{
    std::error_code error;
    const bool configExists = std::filesystem::exists(configPath, error);

    if (error)
    {
        LogConfigurationWarning("Unable to access " + configPath.string() + "; using defaults.");
        return Config::CreateDefault();
    }

    if (!configExists)
    {
        std::cout << "Configuration file not found. Creating default configuration at "
                  << configPath.string() << ".\n";
        CreateDefaultConfigFile();
        return Config::CreateDefault();
    }

    std::ifstream input(configPath);

    if (!input)
    {
        LogConfigurationWarning("Unable to open " + configPath.string() + "; using defaults.");
        return Config::CreateDefault();
    }

    nlohmann::json json;

    try
    {
        input >> json;
    }
    catch (const nlohmann::json::exception& exception)
    {
        LogConfigurationWarning(
            "Unable to parse " + configPath.string() + ": " + exception.what() + "; using defaults.");
        return Config::CreateDefault();
    }

    if (!json.is_object())
    {
        LogConfigurationWarning("Configuration root must be a JSON object; using defaults.");
        return Config::CreateDefault();
    }

    try
    {
        Config config = Config::CreateDefault();

        config.locationMode = ReadStringValue(
            json,
            "locationMode",
            config.locationMode,
            {"manual", "user", "in_game"});
        config.latitude = ReadCoordinate(json, "latitude", DEFAULT_LATITUDE, MIN_LATITUDE, MAX_LATITUDE);
        config.longitude = ReadCoordinate(json, "longitude", DEFAULT_LONGITUDE, MIN_LONGITUDE, MAX_LONGITUDE);
        config.weatherProvider = ReadStringValue(json, "weatherProvider", config.weatherProvider, {"mock"});
        config.updateInterval = ReadUpdateInterval(json);
        config.units = ReadStringValue(json, "units", config.units, {"metric", "imperial"});
        config.logLevel = ReadStringValue(
            json,
            "logLevel",
            config.logLevel,
            {"trace", "debug", "info", "warning", "error"});

        return config;
    }
    catch (const nlohmann::json::exception& exception)
    {
        LogConfigurationWarning(
            "Unable to validate " + configPath.string() + ": " + exception.what() + "; using defaults.");
        return Config::CreateDefault();
    }
}

void ConfigManager::CreateDefaultConfigFile() const
{
    const std::filesystem::path parentPath = configPath.parent_path();

    if (!parentPath.empty())
    {
        std::error_code error;
        std::filesystem::create_directories(parentPath, error);

        if (error)
        {
            LogConfigurationWarning(
                "Unable to create configuration directory " + parentPath.string() + "; using defaults.");
            return;
        }
    }

    std::ofstream output(configPath);

    if (!output)
    {
        LogConfigurationWarning("Unable to create " + configPath.string() + "; using defaults.");
        return;
    }

    output << SerializeConfig(Config::CreateDefault()).dump(4) << '\n';

    if (!output)
    {
        LogConfigurationWarning("Unable to finish writing " + configPath.string() + "; using defaults.");
    }
}
