#pragma once

#include "ILocationProvider.hpp"

/**
 * @brief Provides the manually configured geographic coordinates.
 */
class ManualLocationProvider : public ILocationProvider
{
public:
    /**
     * @brief Creates a provider for the supplied manual coordinates.
     * @param latitude The configured latitude in decimal degrees.
     * @param longitude The configured longitude in decimal degrees.
     */
    ManualLocationProvider(double latitude, double longitude);

    /**
     * @brief Gets the configured manual location.
     * @return A location containing the configured latitude and longitude.
     */
    Location GetLocation() override;

private:
    double latitude;
    double longitude;
};
