#include "HttpClient.hpp"

#include <curl/curl.h>

namespace
{
    class CurlGlobalState
    {
    public:
        CurlGlobalState()
            : result(curl_global_init(CURL_GLOBAL_DEFAULT))
        {
        }

        ~CurlGlobalState()
        {
            if (result == CURLE_OK)
            {
                curl_global_cleanup();
            }
        }

        CURLcode result;
    };

    size_t WriteResponse(char* data, size_t size, size_t count, void* userData)
    {
        std::string* body = static_cast<std::string*>(userData);
        body->append(data, size * count);
        return size * count;
    }
}

HttpClient::HttpClient(long timeoutSeconds)
    : timeoutSeconds(timeoutSeconds)
{
}

HttpResponse HttpClient::Get(const std::string& url) const
{
    static const CurlGlobalState curlGlobalState;
    HttpResponse response;

    if (!url.starts_with("https://"))
    {
        response.errorMessage = "Only HTTPS requests are supported.";
        return response;
    }

    if (curlGlobalState.result != CURLE_OK)
    {
        response.errorMessage = curl_easy_strerror(curlGlobalState.result);
        return response;
    }

    CURL* curl = curl_easy_init();

    if (curl == nullptr)
    {
        response.errorMessage = "Unable to initialize HTTP client.";
        return response;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeoutSeconds);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteResponse);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.body);

    const CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
        response.errorMessage = curl_easy_strerror(result);
        curl_easy_cleanup(curl);
        return response;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.statusCode);
    curl_easy_cleanup(curl);

    if (response.statusCode < 200 || response.statusCode >= 300)
    {
        response.errorMessage = "HTTP request returned status " + std::to_string(response.statusCode) + ".";
        return response;
    }

    response.success = true;
    return response;
}
