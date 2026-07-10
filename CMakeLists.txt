cmake_minimum_required(VERSION 3.20)

project(LiveDrive VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(LiveDrive
    app/main.cpp
    config/Config.cpp
    config/ConfigManager.cpp
    providers/ManualLocationProvider.cpp
    providers/MockLocationProvider.cpp
    providers/MockWeatherProvider.cpp
)

target_link_libraries(LiveDrive PRIVATE nlohmann_json::nlohmann_json)
