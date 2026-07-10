#include "ManualLocationProvider.hpp"

ManualLocationProvider::ManualLocationProvider(double latitude, double longitude)
    : latitude(latitude)
    , longitude(longitude)
{
}

Location ManualLocationProvider::GetLocation()
{
    Location location;

    location.latitude = latitude;
    location.longitude = longitude;

    return location;
}
