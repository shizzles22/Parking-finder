#ifndef FINDPARK_H
#define FINDPARK_H

#include <QDialog>
#include <QWidget>
#include <QStringListModel>


namespace Ui {
class findpark;
}

class findpark : public QDialog
{
    Q_OBJECT

public:
    explicit findpark(QWidget *parent = nullptr);
    ~findpark();

private slots:
    void on_pushButton_clicked();

private:
    QStringListModel *listModel; // Model to display results in QListView
    Ui::findpark *ui;
    double userLat;
    double userLon;
};

#endif // FINDPARK_H
