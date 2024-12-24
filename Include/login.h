#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>


namespace Ui {
class login;
}

extern QString name;
extern QString currentCity;

class login : public QWidget
{
    Q_OBJECT

public:

    explicit login(QWidget *parent = nullptr);
    virtual ~login();



public slots:
    void on_pushButton_clicked();


private:


    Ui::login *ui;
};


#endif // LOGIN_H
