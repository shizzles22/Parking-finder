#include "database.h"
#include <algorithm> // For std::sort
#include <iostream>

// Haversine formula to calculate distance between two coordinates
double database::coordinatesToDistance(double lat1, double lon1, double lat2, double lon2) const {
    constexpr double R = 6371.0; // Earth's radius in kilometers
    auto degToRad = [](double deg) { return deg * M_PI / 180.0; };

    double dLat = degToRad(lat2 - lat1);
    double dLon = degToRad(lon2 - lon1);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(degToRad(lat1)) * std::cos(degToRad(lat2)) *
                   std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return R * c; // Distance in kilometers
}

database::database(const std::string &city, double radius, double userLat, double userLon)
    : searchRadius(radius), cityName(city), userLatitude(userLat), userLongitude(userLon) {}

void database::createDatabase() {
    try {
        // Load parking data for the given city
        osmApi api; // Create an instance of osmApi to fetch data
        parkingStructure.loadParkingData(cityName, api);

        const auto &parkingLots = parkingStructure.getParkingData(cityName);
        filterByRadius(parkingLots);

        std::cout << "Database created: Found " << filteredParkingLots.size()
                  << " parking lots within " << searchRadius << " km.\n";
    } catch (const std::exception &ex) {
        std::cerr << "Error creating database: " << ex.what() << std::endl;
    }

}

void database::filterByRadius(const std::vector<ParkingLot> &parkingLots) {
    filteredParkingLots.clear();

    for (const auto &lot : parkingLots) {
        double distance = coordinatesToDistance(userLatitude, userLongitude, lot.latitude, lot.longitude);
        if (distance <= searchRadius) {
            // Copy ParkingLot details and add the distance
            filteredParkingLots.push_back({
                lot.latitude,
                lot.longitude,
                lot.accessType,
                lot.parkingType,
                lot.feeType,
                lot.accessibility,
                distance
            });
        }
    }

    // Sort the filtered parking lots by distance (ascending)
    std::sort(filteredParkingLots.begin(), filteredParkingLots.end(),
              [](const FilteredParkingLot &a, const FilteredParkingLot &b) {
                  return a.distance < b.distance;
              });
}

const std::vector<FilteredParkingLot>& database::getFilteredParkingData() const {
    return filteredParkingLots;

}

void database::deleteDatabase() {
    filteredParkingLots.clear();
    std::cout << "Database cleared.\n";
}
