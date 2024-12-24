#include "login.h"
#include "user.h"
#include <ctime>
#include <limits>

// Constructor
user::user(userType type) : lastRequest(std::time(nullptr)), userPlan(type) {}

// Virtual Destructor
user::~user() {}

user& user::getInstance(userType type) {
    static basicUser basicInstance;
    static premiumUser premiumInstance;

    if (type == BASIC) {
        return basicInstance;
    } else {
        return premiumInstance;
    }
}


void user::setCity(const std::string& city) {
    currentCity = QString::fromStdString(city);
}

// Getter for `currentCity`
QString user::getCity() const {
    return currentCity;
}

//Getter for `name`
QString user::getName() const {
    return name;
}

// Check if enough time has passed since the last request
bool user::checkTimeFromLastRequest() {
    time_t currentTime = std::time(nullptr);

    // If the difference exceeds the reset limit, reset the request count
    if (std::difftime(currentTime, lastRequest) >= requestTimeLimit) {
        requestCount = 0; // Reset the count
        return true;
    }
    return false;
}

// Increment the request count
void user::incrementRequestCount() {
    requestCount++;
}

// Check if the request can be processed
bool user::canProcessRequest() {
    if(userPlan == 1 ){
        return true;
    }
    else if (!requestLimitExceeded()){
        return true;
    }
    else
        checkTimeFromLastRequest(); // Ensure the timer is updated
    return false; // Check if under the request limit
}

// Add a request if allowed
bool basicUser::addRequest() {
    if (canProcessRequest()) {
        incrementRequestCount();
        lastRequest = std::time(nullptr); // Update last request time
        return true;
    }
    return false; // Deny if request limit exceeded
}
bool user::requestLimitExceeded() const {
    return requestCount >= requestLimit; // Default check
}

bool basicUser::canProcessRequest() {
    return requestCount < requestLimit; // Basic users have a limited request count
}


// basicUser Class Constructor
basicUser::basicUser() : user(BASIC) {
    requestLimit = 3; // Limit of 3 requests for basic users
}

// Implement the Prototype Design Pattern for basicUser
std::unique_ptr<user> basicUser::clone() const {
    return std::make_unique<basicUser>(); // Explicitly create a new instance
}

// premiumUser Class Constructor
premiumUser::premiumUser() : user(PREMIUM) {
    requestLimit = std::numeric_limits<int>::max(); // Unlimited requests
}

// premiumUser::addRequest Implementation
bool premiumUser::addRequest() {
    return true; // Premium users always have unlimited requests
}


// Implement the Prototype Design Pattern for premiumUser
std::unique_ptr<user> premiumUser::clone() const {
    return std::make_unique<premiumUser>();
}
