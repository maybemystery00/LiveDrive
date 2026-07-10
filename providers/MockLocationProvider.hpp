#pragma once

#include "ILocationProvider.hpp"

/**
 * @brief Provides a fixed location for local development and testing.
 */
class MockLocationProvider : public ILocationProvider
{
public:
    /**
     * @brief Gets the fixed mock location.
     * @return The predefined Berlin, Germany location.
     */
    Location GetLocation() override;
};
