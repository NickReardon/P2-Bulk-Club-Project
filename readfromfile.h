#ifndef READFROMFILE_H
#define READFROMFILE_H

#include <QDialog>

#include <QFileDialog>
#include <QtDebug>
#include <QFile>
#include <QDate>
#include "dbmanager.h"

namespace Ui {
class readFromFile;
}

class readFromFile : public QDialog
{
    Q_OBJECT

public:
    explicit readFromFile(QWidget *parent = nullptr);
    ~readFromFile();

private slots:
    void on_openFileButton_released();

    void on_readFileButton_released();

private:
    Ui::readFromFile *ui;
    DbManager dbManager = DbManager("C:/Users/Nick/source/repos/P2-Bulk-Club-Project/BulkClub.db");

    QString filename;

    QDate date;
    int id;
    QString product;
    double price;
    int quantity;


    QString name;
    QString type;

};

#endif // READFROMFILE_H
