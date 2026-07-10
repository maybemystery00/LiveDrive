#include "OpenMeteoWeatherProvider.hpp"

#include <iomanip>
#include <sstream>

#include <nlohmann/json.hpp>

namespace
{
    std::string BuildRequestUrl(const Location& location)
    {
        std::ostringstream url;
        url << std::fixed << std::setprecision(6);
        url << "https://api.open-meteo.com/v1/forecast?latitude=" << location.latitude;
        url << "&longitude=" << location.longitude;
        url << "&current=temperature_2m,relative_humidity_2m,rain,showers,cloud_cover,wind_speed_10m,visibility,surface_pressure";
        url << "&temperature_unit=celsius&wind_speed_unit=kmh&precipitation_unit=mm";
        return url.str();
    }

    float ReadCurrentValue(const nlohmann::json& current, const char* name)
    {
        if (!current.contains(name) || !current.at(name).is_number())
        {
            throw nlohmann::json::type_error::create(302, std::string("Missing numeric current.") + name, &current);
        }

        return current.at(name).get<float>();
    }
}

OpenMeteoWeatherProvider::OpenMeteoWeatherProvider(long timeoutSeconds)
    : httpClient(timeoutSeconds)
{
}

WeatherSnapshot OpenMeteoWeatherProvider::Fetch(const Location& location)
{
    lastFetchSuccessful = false;
    lastError.clear();

    const HttpResponse response = httpClient.Get(BuildRequestUrl(location));

    if (!response.success)
    {
        lastError = response.errorMessage;
        return {};
    }

    try
    {
        const nlohmann::json json = nlohmann::json::parse(response.body);
        const nlohmann::json& current = json.at("current");
        WeatherSnapshot weather;

        weather.temperatureC = ReadCurrentValue(current, "temperature_2m");
        weather.humidity = ReadCurrentValue(current, "relative_humidity_2m");
        // Rain and showers are both liquid precipitation; snowfall is excluded because WeatherSnapshot has no snow field.
        weather.rainIntensity = ReadCurrentValue(current, "rain") + ReadCurrentValue(current, "showers");
        weather.cloudCover = ReadCurrentValue(current, "cloud_cover");
        weather.windSpeed = ReadCurrentValue(current, "wind_speed_10m");
        weather.visibility = ReadCurrentValue(current, "visibility");
        weather.pressure = ReadCurrentValue(current, "surface_pressure");

        lastFetchSuccessful = true;
        return weather;
    }
    catch (const nlohmann::json::exception& exception)
    {
        lastError = exception.what();
        return {};
    }
}

bool OpenMeteoWeatherProvider::IsLastFetchSuccessful() const
{
    return lastFetchSuccessful;
}

const std::string& OpenMeteoWeatherProvider::GetLastError() const
{
    return lastError;
}
