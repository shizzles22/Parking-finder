#include "findpark.h"
#include <QtWidgets/qwidget.h>
#include <ctime>
#include "login.h"
#include "freesearch.h"
#include "ui_login.h"
#include "user.h"


QString name = "";
QString  currentCity = "";

 login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Free user");
    ui->comboBox->addItem("Premium user");


    ui->city_name->addItem("Toronto");
    ui->city_name->addItem("Ottawa");
    ui->city_name->addItem("Calgary");
    ui->city_name->addItem("Vancouver");
    ui->city_name->addItem("Hamilton");

}

login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{
    currentCity = ui->city_name->currentText();
    name = ui->user_name->text();
    QString userType = ui->comboBox->currentText(); // QComboBox for user type

    user::userType selectedType = (ui->comboBox->currentIndex() == 1) ? user::PREMIUM : user::BASIC;

    // Set the user type and city in the singleton instance
    user& currentUser = user::getInstance(selectedType); // Pass the user type
    currentUser.setCity(currentCity.toStdString());

    // Determine user type and initialize appropriately
    if (selectedType == user::PREMIUM) {
        findpark *fp = new findpark(this);
        fp->show();
        hide();
    } else {
        freeSearch *fs = new freeSearch(this);
        fs->show();
        hide();
    }


}







