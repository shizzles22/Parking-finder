#ifndef OSM_API_H
#define OSM_API_H

#include <QtCore/qobject.h>
#include <string>

class osmApi {
public:
    osmApi();
    std::string getParkingData(const std::string &city);
    static QString reverseGeocode(double latitude, double longitude);


private:
    std::string encodeCityName(const std::string &city) const;
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif // OSM_API_H
