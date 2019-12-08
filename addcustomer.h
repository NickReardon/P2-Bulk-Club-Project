#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include <QDialog>
#include "dbmanager.h"
/**
 * @file
 */


/**
 * \class addCustomer
 *
 * \brief class for adding customer and prompting its UI
 *
 * addCustomer collects all the information needed for a new customer
 * and performs validity input for each data field. The class requires
 * existing SQL database.
 */

namespace Ui {
class addCustomer;
}


class addCustomer : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * Constructor sets up ui for addCustomer
     * @param *parent - for QDialog
     */
    explicit addCustomer(QWidget *parent = nullptr);
    /**
     * @brief Destructor
     *
     * Close the addCustomer UI
     */
    ~addCustomer();

private slots:
    /**
     * @brief cancels addCustomer execution and closes UI
     * @return nothing - void
     */
    void on_cancelCustomerButton_clicked();

    /**
     * @brief on user click, validates all data input for user data values and adds to DB
     * @return nothing - void
     *
     */
    void on_addCustomerButton_clicked();

private:
    /**
     * @brief points to addCustomer UI

     */
    Ui::addCustomer *ui;
    DbManager dbManager = DbManager("C:/Users/farna/Documents/P2-Bulk-Club-Project/BulkClub.db");
};

#endif // ADDCUSTOMER_H
