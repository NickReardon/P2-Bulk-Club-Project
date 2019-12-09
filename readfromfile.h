#ifndef READFROMFILE_H
#define READFROMFILE_H

#include <QDialog>

#include <QFileDialog>
#include <QtDebug>
#include <QFile>
#include <QDate>
#include "dbmanager.h"
/**
 * @file
 */


/**
 * \class readFromFile
 *
 * \brief class for reading in data for the DB from a file.
 * intitalizes UI to select and read a file from userend to
 * import data
 *
 */


namespace Ui {
class readFromFile;
}

class readFromFile : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief readFromFile constructor
     *
     * Constructor sets up ui for readFromFile window
     * @param *parent - for QDialog
     */
    explicit readFromFile(QWidget *parent = nullptr);
    /**
    * @brief Destructor
    *
    * Closes UI upon requested exit
    */
    ~readFromFile();

private slots:

    /**
    * @brief upon user click, prompts manager to select a file
    * to read data and import to DB. Verfies and selects filepath
    */
    void on_openFileButton_released();

    /**
    * @brief reads in all sorted data from selected file into the database
    */
    void on_readFileButton_released();

private:
    Ui::readFromFile *ui;
    DbManager dbManager = DbManager("C:/Users/farna/documents/P2-Bulk-Club-Project/BulkClub.db");

    ///Holds filename for desired filepath
    QString filename;

    ///Holds date for node
    QDate date;

    ///Holds id for node
    int id;
    ///Holds product for node
    QString product;
    ///Holds price for node
    double price;
    ///Holds quantity fornode
    int quantity;


    ///Holds membership name for node
    QString name;
    ///Holds membership type for node
    QString type;

};

#endif // READFROMFILE_H
