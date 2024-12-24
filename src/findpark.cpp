#include "findpark.h"
#include "login.h"
#include "user.h"
#include "filters.h"
#include "ui_findpark.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <iostream>
#include <QStringListModel>
#include <QStringList>


findpark::findpark(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::findpark),
    listModel(new QStringListModel(this)) // Initialize model
{
    ui->setupUi(this);
    ui->listView->setModel(listModel);
    ui -> nameLabel->setText(name);
    ui->comboBox->addItem("0.5km");
    ui->comboBox->addItem("1km");
    ui->comboBox->addItem("2km");
    ui->comboBox->addItem("3km");
    ui->comboBox->addItem("4km");
    ui->comboBox->addItem("5km");

}

findpark::~findpark()
{
    delete ui;
}



void findpark::on_pushButton_clicked()
{
    QString input = ui->latlongInput->text(); // Format: "1.44, 1.44"

    QStringList coordinates = input.split(", ");

    if (coordinates.size() == 2) {

        bool latOk, lonOk;
        double latitude = coordinates[0].toDouble(&latOk);
        double longitude = coordinates[1].toDouble(&lonOk);


        if (!latOk || !lonOk) {
            QMessageBox::warning(this, "Input Error", "Invalid latitude or longitude format.");
            return;
        }

        double searchRadius = 4.0; // Default radius
        QString selectedRadius = ui->comboBox->currentText();


        // Converting radius string to double (e.g., "0.5km" -> 0.5)
        if (selectedRadius.endsWith("km")) {
            selectedRadius.chop(2); // Removing "km" from the end
            bool conversionOk;
            searchRadius = selectedRadius.toDouble(&conversionOk); // conversion to double

            if (!conversionOk) {
                QMessageBox::warning(this, "Input Error", "Failed to parse radius.");
                searchRadius = 4.0; // Revert to default
            }
        } else {
            QMessageBox::warning(this, "Input Error", "Radius selection is invalid.");
        }



        // Initializing the database

        database db(user::getInstance(user::PREMIUM).getCity().toStdString(), searchRadius, latitude, longitude);
        db.createDatabase();

        // Retrieving filtered data
        auto parkingLots = db.getFilteredParkingData();

        // Applying Filters
        if (ui->publicButton->isChecked()) {
            parkingLots = filters::applyAccessTypeFilter(parkingLots, true);
        }
        if (ui->undergroundButton->isChecked()) {
            parkingLots = filters::applyParkingTypeFilter(parkingLots, "underground");
        }
        if (ui->freeButton->isChecked()) {
            parkingLots = filters::applyFeeFilter(parkingLots, false); // Free parking
        }
        if (ui->accessibilityButton->isChecked()) {
            parkingLots = filters::applyDisabilityFilter(parkingLots, true); // Accessible parking
        }

        // Sorting and Displaying Data
        std::sort(parkingLots.begin(), parkingLots.end(),
                  [](const FilteredParkingLot &a, const FilteredParkingLot &b) {
                      return a.distance < b.distance;
                  });

        QStringList parkingList;
        for (const auto& lot : parkingLots) {
            QString coordinates = QString("Coordinates: Latitude: %1, Longitude: %2 | Distance: %3 km")
            .arg(lot.latitude)
                .arg(lot.longitude)
                .arg(QString::number(lot.distance, 'f', 3));

            QString filters = QString("Access: %1 | Fee: %2 | Parking Type: %3 | Accessibility: %4")
                                  .arg(QString::fromStdString(lot.accessType))
                                  .arg(QString::fromStdString(lot.feeType))
                                  .arg(QString::fromStdString(lot.parkingType))
                                  .arg(lot.accessibility ? "Yes" : "No");

            parkingList.append(coordinates);
            parkingList.append(filters);
            parkingList.append(""); // Blank line for spacing
        }

        listModel->setStringList(parkingList);
        ui->listView->setModel(listModel);

        qDebug() << "User Lat:" << userLat << ", Lon:" << userLon;
    } else {
        qDebug() << "Invalid format! Use '1.44, 1.44 (lat, lon).";
    }
}

