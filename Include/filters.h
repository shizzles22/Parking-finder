#ifndef FILTERS_H
#define FILTERS_H

#include <vector>
#include "database.h" // Include the database for FilteredParkingLot

class filters {
public:
    // Apply Fee Filter: free or paid
    static std::vector<FilteredParkingLot> applyFeeFilter(
        const std::vector<FilteredParkingLot>& lots, bool hasFee);

    // Apply Access Type Filter: public or private
    static std::vector<FilteredParkingLot> applyAccessTypeFilter(
        const std::vector<FilteredParkingLot>& lots, bool isPublic);

    // Apply Accessibility Filter: accessible or not
    static std::vector<FilteredParkingLot> applyDisabilityFilter(
        const std::vector<FilteredParkingLot>& lots, bool hasDisability);

    static std::vector<FilteredParkingLot> applyParkingTypeFilter(
        const std::vector<FilteredParkingLot>& lots, const std::string& parkingType);

};

#endif // FILTERS_H
