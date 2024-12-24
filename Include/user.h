#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>
#include <memory>
#include "login.h"


using namespace std;


class user {
public:

    enum userType {
        BASIC,
        PREMIUM
    };

    // Singleton accessor with a concrete user type
    static user& getInstance(userType type);

    virtual ~user();

    // Member Functions
    void setCity(const string& city);
    QString getCity() const;
    QString getName() const;
    virtual bool addRequest() = 0;
    bool canProcessRequest();
    virtual unique_ptr<user> clone() const = 0; // Prototype Pattern

    // Setters and Getters for latitude and longitude
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

protected:
    // Constructor and Virtual Destructor
    explicit user(userType type);
    int requestLimit = 0;
    double latitude = 0.0; // User's latitude
    double longitude = 0.0; // User's longitude
    time_t lastRequest;
    int requestCount = 0;
    const int requestResetDays = 30;
    const int requestTimeLimit = requestResetDays * 24 * 60 * 60;

    bool checkTimeFromLastRequest();
    void incrementRequestCount();
    virtual bool requestLimitExceeded() const;

private:
    userType userPlan;

};

// Derived Classes
class basicUser : public user {
public:
    basicUser();
    unique_ptr<user> clone() const override;
    bool checkTimeFromLastRequest();
    bool canProcessRequest();
    bool addRequest() override;
};

class premiumUser : public user {
public:
    premiumUser();
    bool addRequest() override;
    unique_ptr<user> clone() const override;
};

class premiumUser;

#endif
