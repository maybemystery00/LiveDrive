#include "MockLocationProvider.hpp"

Location MockLocationProvider::GetLocation()
{
    Location location;

    location.latitude = 52.5200;
    location.longitude = 13.4050;
    location.city = "Berlin";
    location.country = "Germany";
    location.timezone = "Europe/Berlin";

    return location;
}
