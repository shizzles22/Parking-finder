#ifndef FREESEARCH_H
#define FREESEARCH_H

#include <QDialog>
#include <QStringListModel>


namespace Ui {
class freeSearch;
}

class freeSearch : public QDialog
{
    Q_OBJECT

public:
    explicit freeSearch(QWidget *parent = nullptr);
    ~freeSearch();

private slots:
    void on_pushButton_clicked();

private:
    QStringListModel *listModel; // Model to display results in QListView
    void searchDatabase(double latitude, double longitude); // Helper functions
    Ui::freeSearch *ui;
};

#endif // FREESEARCH_H
