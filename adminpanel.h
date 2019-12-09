#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include "dbmanager.h"
#include "addcustomer.h"
#include "confirmupdate.h"
#include "purchase.h"
#include "expiredisplay.h"
/**
 * @file
 */


/**
 * \class adminPanel
 *
 * \brief main class for admin/store manager
 * contains UI and all major functionality for the manager of the bulk club
 * such as viewing sales report, updating customer, product, inventory, etc
 */


namespace Ui {
class adminPanel;
}

class adminPanel : public QDialog
{
    Q_OBJECT

public:

    /**
    * @brief Constructor
    *
    * Constructor sets up ui for adminPanel
    * @param *parent - for QDialog
    */
    explicit adminPanel(QWidget *parent = nullptr);
    /**
    * @brief Destructor
    *
    * Close the adminPanel UI
    */
    ~adminPanel();

    /**
    * @brief updates the product page when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void updateReportProductView();

    /**
    * @brief updates the total value in sales report when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void updateTotalLabel();

    /**
    * @brief updates the member page in sales report when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void updateReportMemberView();

    /**
    * @brief updates the entire sales report table view page when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void updateReport();

    /**
    * @brief updates the total regular members view page when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void update_ReportRegularMembeCount();

    /**
    * @brief updates the total executive members view page when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void update_ReportExecutiveMemberCount();

    /**
    * @brief updates the total purchases by members view page when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void updatePurchases();

    void totalView();
    
    /**
    * @brief updates the total customers by members view page when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void updateCustomers();
    
    /**
    * @brief updates the total products by members view page when a modification to the DB has been made
    * such as a purchase
    * @return void - nothing
    */
    void updateProducts();
    
private slots:
    /**
    * @brief cancels all operations, closes adminPanel UI, logs admin/manager out of the program
    * @return void - nothing
    */
    void on_logoutButton_clicked();

    /**
    * @brief upon click, beings execution for adding a customer node with its data to DB
    * executes addCustomer, verifies data input, and adds member with specified input data
    * values to the DB.
    *
    * @return void - nothing
    */
    void on_addCustomerButton_clicked();

    /**
    * @brief upon click, beings execution for generating a sales report
    *
    * @return void - nothing
    */
    void on_GenerateReportButton_released();

    void on_salesReportCalendar_clicked(const QDate &date);

    void on_salesReportCalendar_selectionChanged();

    /**
    * @brief upon click, beings execution for adding a product to the DB
    *
    * @return void - nothing
    */
    void on_productAdd_clicked();

    /**
    * @brief upon click, beings execution for deleting a product from the DB
    *
    * @return void - nothing
    */
    void on_productDel_clicked();

    void on_testButton_clicked();

    /**
    * @brief upon click, beings execution for deleting a customer from the DB
    *
    * @return void - nothing
    */
    void on_removeCustomerButton_clicked();

    /**
    * @brief upon click, beings execution for upgrading an existing customer
    * or downagrading an existing customer membership type from either
    * regular to executive and the other way around
    *
    * @return void - nothing
    */
    void on_upgradeCustomer_clicked();

    /**
    * @brief upon click, generates sales report for products
    *
    * @return void - nothing
    * @param &index - determines index cell to be found in db
    */
    void on_ReportProductView_activated(const QModelIndex &index);

    /**
    * @brief upon click, generates sales report for members
    *
    * @return void - nothing
    * @param &index - determines index cell to be found in db
    */
    void on_ReportMemberView_pressed(const QModelIndex &index);

    void on_ReportProductView_pressed(const QModelIndex &index);

    /**
    * @brief upon click, begins execustion for reading data from a file.
    *
    * Manager is able to select a file of data, then once selected, the
    * program imports data from the selected file path to the DB
    *
    * @return void - nothing
    */
    void on_readFromFileButton_released();

    /**
    * @brief upon click, restores display to show all members with
    * their values
    *
    * @return void - nothing
    */
    void on_showallButton_clicked();

    /**
    * @brief upon click, restores display to show all products with
    * their values
    *
    * @return void - nothing
    */
    void on_showallProducts_clicked();

    /**
    * @brief upon entering search for user specified product, execution
    * begins for returning the results of the search in DB for the user
    *
    * @return void - nothing
    */
    void on_productSearch_returnPressed();

    /**
    * @brief upon entering search for user specified product, execution
    * begins for returning the results of the search in DB for the user
    *
    * @return void - nothing
    */
    void on_purchaseSearch_returnPressed();

    /**
    * @brief upon user click, prompts a list of customer from the DB
    * whos memberships are expiring in the user specified months
    *
    * @return void - nothing
    */
    void on_expireButton_released();

    void on_showBox_currentIndexChanged(int index);

private:
    ///contains pointer for adminPanel UI
    Ui::adminPanel *ui;
    DbManager dbManager = DbManager("C:/Users/farna/documents/P2-Bulk-Club-Project/BulkClub.db");

    ///Holds temp date for selection
    QDate tempDate;

    ///Holds first date range for report
    QDate firstDate;
    ///Holds end date range for report
    QDate endDate;
};

#endif // ADMINPANEL_H
