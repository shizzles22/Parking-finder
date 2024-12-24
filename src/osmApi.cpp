#include "osmApi.h"
#include <curl/curl.h>
#include <stdexcept>
#include <sstream>


osmApi::osmApi() {}

std::string osmApi::encodeCityName(const std::string &city) const {
    std::ostringstream encoded;
    for (char c : city) {
        if (c == ' ') {
            encoded << "%20";
        } else {
            encoded << c;
        }
    }
    return encoded.str();
}

size_t osmApi::writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string osmApi::getParkingData(const std::string &city) {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("CURL initialization failed");
    }

    std::string encodedCity = encodeCityName(city);
    std::string url = "http://overpass-api.de/api/interpreter?data=[out:json];area[name=\"" +
                      encodedCity +
                      "\"]->.searchArea;(node[\"amenity\"=\"parking\"](area.searchArea););out;";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
    }

    curl_easy_cleanup(curl);
    return response;
}

