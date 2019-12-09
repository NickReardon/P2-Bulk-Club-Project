#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include "adminpanel.h"
/**
 * @file
 */


/**
 * \class MainWindow
 *
 * \brief class for prompting a Login UI with fields for username and password
 *
 * login UI that prompts user to enter data for their specific username and password.
 * The data entry is validated then verifies whether that username and password is in the DB.
 */



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * Constructor sets up ui for login window
     * @param *parent - for QDialog
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
    * @brief Destructor
    *
    * Closes UI upon requested exit
    */
    ~MainWindow();

private slots:

    /**
     * @brief clears data in both username and password fields to a a blank "" when clicked
     */
    void on_clearButton_clicked();

    /**
    * @brief upon user click, extracts data from user and pass data fields input from user. After extraction
    * , input is validated and verified that it exists in the admin DB. Prompts an error if user doesnt exist,
    * or if input is not validated.
    */
    void on_loginButton_clicked();

    void on_usernameEdit_returnPressed();

    void on_passwordEdit_returnPressed();

private:
    Ui::MainWindow *ui;

    DbManager dbManager = DbManager("C:/Users/farna/documents/P2-Bulk-Club-Project/BulkClub.db");
};

#endif // MAINWINDOW_H
