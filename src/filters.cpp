#include "filters.h"

std::vector<FilteredParkingLot> filters::applyFeeFilter(
    const std::vector<FilteredParkingLot>& lots, bool hasFee) {

    std::vector<FilteredParkingLot> filteredLots;
    for (const auto& lot : lots) {
        if ((hasFee && lot.feeType == "paid") || (!hasFee && lot.feeType == "free")) {
            filteredLots.push_back(lot);
        }
    }
    return filteredLots;
}

std::vector<FilteredParkingLot> filters::applyAccessTypeFilter(
    const std::vector<FilteredParkingLot>& lots, bool isPublic) {

    std::vector<FilteredParkingLot> filteredLots;
    for (const auto& lot : lots) {
        if ((isPublic && lot.accessType == "public") || (!isPublic && lot.accessType == "private")) {
            filteredLots.push_back(lot);
        }
    }
    return filteredLots;
}

std::vector<FilteredParkingLot> filters::applyDisabilityFilter(
    const std::vector<FilteredParkingLot>& lots, bool hasDisability) {

    std::vector<FilteredParkingLot> filteredLots;
    for (const auto& lot : lots) {
        if (lot.accessibility == hasDisability) {
            filteredLots.push_back(lot);
        }
    }
    return filteredLots;
}

std::vector<FilteredParkingLot> filters::applyParkingTypeFilter(
    const std::vector<FilteredParkingLot>& lots, const std::string& parkingType) {

    std::vector<FilteredParkingLot> filteredLots;
    for (const auto& lot : lots) {
        if (lot.parkingType == parkingType) {
            filteredLots.push_back(lot);
        }
    }
    return filteredLots;
}
