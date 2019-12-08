#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include "dbmanager.h"
#include "addcustomer.h"
#include "confirmupdate.h"

namespace Ui {
class adminPanel;
}

/**
 * @class adminPanel
 * @brief The adminPanel class
 * Ui panel for admin userType. Contains options for adding a customer node
 * , genreating a report, adding and deleting a product, searching for products,
 * removing a customer node, and upgrading a customer node.
 */
class adminPanel : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor
     *
     * Constructor sets up ui for admin panel
     * @param *parent - for QDialog
     */
    explicit adminPanel(QWidget *parent = nullptr);
    /**
     * @brief Destructor
     *
     * Close the adminPanel UI
     */
    ~adminPanel();

private slots:
    /**
     * @brief logs the userout on request
     * @return void - nothing
     */
    void on_logoutButton_clicked();

    /**
     * @brief on user click, launches and executes the addCustomer ui and class
     *
     * initiates sequence of addcustomer for admins only with and adds to DB when
     * successful
     * @return void - nothing
     *
     */
    void on_addCustomerButton_clicked();

    /**
     * @brief prompts user to select a date, then executes the generate sales report
     * function from DBManager.
     * @return void - nothing [slot]
     */
    void on_GenerateReportButton_released();

    void on_salesReportCalendar_clicked(const QDate &date);

    void on_salesReportCalendar_selectionChanged();

    void on_productAdd_clicked();

    void on_productDel_clicked();

    void on_testButton_clicked();

    void on_productSearch_editingFinished();

    void on_removeCustomerButton_clicked();

    void on_upgradeCustomer_clicked();

private:

    Ui::adminPanel *ui; /**< ui pointer*/
    DbManager dbManager = DbManager("C:/Users/farna/Documents/P2-Bulk-Club-Project/BulkClub.db");

    QDate tempDate;

};

#endif // ADMINPANEL_H
