#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QDialog>
#include "dbmanager.h"
/**
 * @file
 */


/**
 * \class products
 *
 * \brief class for managing product inventory and quantity
 *
 * from admin user prespective, class launces a UI which allows manager
 * to enter a product name and edit its quanitity value for inventory
 */

namespace Ui
{
class products;
}

class products : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * Constructor sets up ui for products window
     * @param *parent - for QDialog
     */
    explicit products(int t, QWidget *parent = nullptr);
    /**
    * @brief Destructor
    *
    * Closes UI upon requested exit
    */
    ~products();

private slots:
    /**
    * @brief Upon user click, executes code to modify inventory of
    * user specified product, by verfiying product, data input, then
    * binding to DB with date.
    * @return nothing - void
    */
    void on_okButton_clicked();

    /**
    * @brief upon user click, cancels all operations and closes product UI
    * @return nothing - void
    */
    void on_cancelButton_clicked();

private:
    Ui::products *ui;

    DbManager dbManager = DbManager("C:/Users/farna/documents/P2-Bulk-Club-Project/BulkClub.db");
};


#endif // PRODUCTS_H
