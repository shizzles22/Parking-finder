#ifndef DATABASE_H
#define DATABASE_H

#include "parkingstructure.h"
#include <string>
#include <vector>
#include <cmath>

// Enhanced structure to hold ParkingLot details and distance
struct FilteredParkingLot {
    double latitude;
    double longitude;
    std::string accessType;      // Public/Private
    std::string parkingType;     // Underground/Not
    std::string feeType;         // Free/Paid
    bool accessibility;          // Accessible spots available
    double distance;             // Distance from user coordinates
};

class database {
public:
    database(const std::string &city, double radius, double userLat, double userLon);

    void createDatabase(); // Create and filter parking data
    void deleteDatabase(); // Clear filtered data
    const std::vector<FilteredParkingLot>& getFilteredParkingData() const;

private:
    double searchRadius; // Search radius in km
    std::string cityName;
    double userLatitude;
    double userLongitude;

    ParkingStructure parkingStructure; // Object to interact with ParkingStructure
    std::vector<FilteredParkingLot> filteredParkingLots; // Filtered parking data

    double coordinatesToDistance(double lat1, double lon1, double lat2, double lon2) const;
    void filterByRadius(const std::vector<ParkingLot> &parkingLots);
};

#endif // DATABASE_H
