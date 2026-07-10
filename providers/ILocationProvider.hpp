#pragma once

#include "../core/Location.hpp"

/**
 * @brief Defines a source of normalized geographic locations.
 *
 * Implementations may obtain locations from user settings, ETS2, or another
 * source without exposing those details to the rest of the application.
 */
class ILocationProvider
{
public:
    /** @brief Destroys the provider through its interface. */
    virtual ~ILocationProvider() = default;

    /**
     * @brief Gets the current location from this provider.
     * @return A normalized geographic location.
     */
    virtual Location GetLocation() = 0;
};
