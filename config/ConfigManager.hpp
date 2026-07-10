#pragma once

#include "Config.hpp"

#include <filesystem>

/**
 * @brief Loads, validates, and creates the LiveDrive configuration file.
 */
class ConfigManager
{
public:
    /**
     * @brief Creates a manager for the supplied configuration-file path.
     * @param configPath The JSON file to load and create when absent.
     */
    explicit ConfigManager(std::filesystem::path configPath);

    /**
     * @brief Loads the configuration, using defaults for missing or invalid values.
     * @return A validated configuration that is safe for the application to use.
     */
    Config Load() const;

private:
    /** Writes the default configuration file when no configuration exists. */
    void CreateDefaultConfigFile() const;

    std::filesystem::path configPath;
};
