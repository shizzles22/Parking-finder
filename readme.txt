Parking Finder System

 Description
The Parking Finder System is a Qtbased application designed to help users search for parking lots near a specified location. The system integrates OpenStreetMap data via API calls and supports dynamic filtering of parking lots based on radius, fee type, access type, and accessibility. It supports two types of users:

 BasicUser: Limited to three searches with fixed filters.
 PremiumUser: Unlimited searches with dynamic filters.

The application employs objectoriented principles and design patterns like Singleton, Prototype, and Decorator for scalability and maintainability.



 Features
1. Search parking lots by latitude and longitude.
2. Filter results by radius, access type (public/private), fee type (free/paid), and parking type (underground, multistorey).
3. Results displayed in a userfriendly GUI using QListView.
4. Reverse geocoding for future implementation to display street addresses.
5. Basic and Premium user functionalities.



 Dependencies

The project uses the following libraries:

1. Qt Framework: Handles GUI components and application flow.
    Required modules: `core`, `gui`, `widgets`, and `network`.
2. cURL: Used for making HTTP requests to the OpenStreetMap API.
3. nlohmann/json: Parses JSON responses from the API.

Install dependencies using:

bash
sudo aptget install qtbase5dev libcurl4openssldev
sudo aptget install libjsoncppdev




For macOS:

bash
brew install qt libcurl nlohmannjson


For Windows:
 Install Qt from [Qt Download](https://www.qt.io/download).
 Install cURL and JSON libraries via vcpkg:
 bash
  vcpkg install curl jsoncpp
  


 How to Compile

 Step 1: Clone the Repository


 Step 2: Open the Project in Qt Creator
1. Launch Qt Creator.
2. Open the `ParkingFinder.pro` file.
3. Ensure the project configuration includes the following in the `.pro` file:

QT += core gui widgets network
CONFIG += c++17
LIBS += lcurl
INCLUDEPATH += /path/to/nlohmann/json/include


 Step 3: Build the Project
1. Run `qmake` to generate the Makefile.
   bash
   qmake

2. Compile the project:
   bash
   make
   

 Step 4: Run the Application
After a successful build, run the application:
bash
./parkSmart
 How to Use

1. Launch the application.
2. Log in as either a BasicUser or PremiumUser.
3. Enter latitude and longitude for the search location.
4. (Premium Users) Select radius and apply filters as needed.
5. View parking lots displayed in the QListView.



 Future Enhancements
1. Implement reverse geocoding to display street addresses.
2. Enhance user interface for better usability.
3. Support offline data storage for frequently searched locations.


