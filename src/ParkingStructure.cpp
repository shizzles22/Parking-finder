#include "parkingstructure.h"
#include <iostream>
#include <stdexcept>

#include <nlohmann/json.hpp>
    using json = nlohmann::json;

ParkingStructure::ParkingStructure() {}

void ParkingStructure::loadParkingData(const std::string &city, osmApi &api) {
    // Check if city is supported
    if (std::find(supportedCities.begin(), supportedCities.end(), city) == supportedCities.end()) {
        throw std::invalid_argument("City not supported: " + city);
    }

    // Fetch API data using osmApi
    std::string response = api.getParkingData(city);

    // Parse and store the data
    parseApiResponse(response, city);
}

void ParkingStructure::parseApiResponse(const std::string &response, const std::string &city) {
    // Parse JSON response
    auto jsonResponse = json::parse(response);

    std::vector<ParkingLot> parkingLots;

    for (const auto &element : jsonResponse["elements"]) {
        ParkingLot lot;

        // Extract latitude and longitude
        lot.latitude = element["lat"];
        lot.longitude = element["lon"];

        // Extract additional tags
        if (element.contains("tags")) {
            auto tags = element["tags"];
            lot.accessType = tags.value("access", "unknown");
            lot.parkingType = tags.value("parking", "unknown");
            lot.feeType = tags.contains("fee") ? (tags["fee"] == "yes" ? "paid" : "free") : "unknown";
            lot.accessibility = tags.value("wheelchair", "no") == "yes";
        }

        parkingLots.push_back(lot);
    }

    cityParkingData[city] = parkingLots;
}

const std::vector<ParkingLot>& ParkingStructure::getParkingData(const std::string &city) const {
    auto it = cityParkingData.find(city);
    if (it == cityParkingData.end()) {
        throw std::runtime_error("No data available for the specified city");
    }
    return it->second;
}

