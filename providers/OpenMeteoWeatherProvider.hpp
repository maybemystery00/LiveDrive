#pragma once

#include "IWeatherProvider.hpp"

#include "../http/HttpClient.hpp"

#include <string>

/** @brief Retrieves normalized current weather from the Open-Meteo API. */
class OpenMeteoWeatherProvider : public IWeatherProvider
{
public:
    /** @brief Creates an Open-Meteo provider with a configurable HTTP timeout. */
    explicit OpenMeteoWeatherProvider(long timeoutSeconds = 10);

    /** @brief Fetches and normalizes current weather for the supplied location. */
    WeatherSnapshot Fetch(const Location& location) override;

    /** @brief Reports whether the most recent fetch completed successfully. */
    bool IsLastFetchSuccessful() const;

    /** @brief Returns the failure description from the most recent unsuccessful fetch. */
    const std::string& GetLastError() const;

private:
    HttpClient httpClient;
    bool lastFetchSuccessful = false;
    std::string lastError;
};
