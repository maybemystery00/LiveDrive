#pragma once

#include <string>

/** @brief Contains the result of an HTTP request without interpreting its body. */
struct HttpResponse
{
    bool success = false;
    long statusCode = 0;
    std::string body;
    std::string errorMessage;
};

/** @brief Performs lightweight HTTPS GET requests for external providers. */
class HttpClient
{
public:
    /** @brief Creates a client with the supplied request timeout in seconds. */
    explicit HttpClient(long timeoutSeconds);

    /** @brief Performs an HTTPS GET request and returns its unparsed response. */
    HttpResponse Get(const std::string& url) const;

private:
    long timeoutSeconds;
};
