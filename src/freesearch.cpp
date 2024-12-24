#include "freesearch.h"
#include "ui_freesearch.h"
#include "login.h"
#include "user.h"
#include "database.h"
#include <QStringListModel>
#include <QMessageBox>
#include <QStringList>
#include <algorithm>


freeSearch::freeSearch(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::freeSearch),
    listModel(new QStringListModel(this))
{
    ui->setupUi(this);
    ui -> nameLabel->setText(name);
    ui->listView->setModel(listModel);

}

freeSearch::~freeSearch()
{
    delete ui;
}

void freeSearch::on_pushButton_clicked()
{

    if (!user::getInstance(user::BASIC).addRequest()) {
        QMessageBox::warning(this, "Request Denied",
                             "You have reached the maximum number of searches allowed. Please upgrade to premium for unlimited searches and filters.");
        return; // Stop the search
    }

    QString input = ui->latlongInput->text(); // Format: "1.44, 1.44"
    QStringList coordinates = input.split(", ");

    if (coordinates.size() == 2) {
        bool latOk, lonOk;
        double latitude = coordinates[0].toDouble(&latOk);
        double longitude = coordinates[1].toDouble(&lonOk);

        if (latOk && lonOk) {
            // Set latitude and longitude in the user singleton
            user::getInstance(user::BASIC).setLatitude(latitude);
            user::getInstance(user::BASIC).setLongitude(longitude);

            // Perform the database search
            searchDatabase(latitude, longitude);
        } else {
            QMessageBox::warning(this, "Input Error", "Invalid latitude or longitude format.");
        }
    } else {
        QMessageBox::warning(this, "Input Error", "Please enter coordinates in 'lat, lon' format.");
    }
}

void freeSearch::searchDatabase(double latitude, double longitude) {
    // Converting QString city to std::string
    std::string city = user::getInstance(user::BASIC).getCity().toStdString();

    // Initializing the database
    database db(city, 4.0, latitude, longitude);
    db.createDatabase();

    // Getting filtered parking data
    auto parkingLots = db.getFilteredParkingData();

    if (parkingLots.empty()) {
        QMessageBox::information(this, "Search Result", "No parking lots found near this location.");
        return;
    }

    // Sorting parking lots by distance in ascending order
    std::sort(parkingLots.begin(), parkingLots.end(),
              [](const auto &a, const auto &b) {
                  return a.distance < b.distance;
              });

    // Preparing data for the QListView
    QStringList parkingList;
    for (const auto &lot : parkingLots) {
        QString coordinates = QString("Coordinates: Latitude: %1, Longitude: %2 | Distance: %3 km")
        .arg(lot.latitude)
        .arg(lot.longitude)
        .arg(QString::number(lot.distance, 'f', 3));

        // Formatting the filters on another line
        QString filters = QString("Access: %1 | Fee: %2 | Parking Type: %3 | Accessibility: %4")
            // .arg(QString::number(lot.distance, 'f', 3)) // Format distance
            .arg(QString::fromStdString(lot.accessType))
            .arg(QString::fromStdString(lot.feeType))
            .arg(QString::fromStdString(lot.parkingType))
            .arg(lot.accessibility ? "Yes" : "No ");

        parkingList.append(coordinates);
        parkingList.append(filters);
        parkingList.append(""); // Add an empty line for spacing
    }

    // Updating the QListView model
    listModel->setStringList(parkingList);
}
