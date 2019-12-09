#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDialog>
#include "dbmanager.h"
/**
 * @file
 */


/**
 * \class purchase
 *
 * \brief class for managing purchases and applying a
 * purchase to a customer node
 */
namespace Ui
{
    class purchase;
}

class purchase : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief purchase
     *
     * Constructor sets up ui for purchases window
     * @param *parent - for QDialog
     */
    explicit purchase(QWidget *parent = nullptr);
    /**
    * @brief Destructor
    *
    * Closes UI upon requested exit
    */
    ~purchase();

private slots:

    /**
    * @brief Upon user click, executes code to modify inventory of
    * user specified purchase, by verfiying product, customer, and ability to purchase
    * and binds to DB, updates val for customer and products
    * @return nothing - void
    */
    void on_purchaseButton_released();

    /**
    * @brief updates quanitity that user has specified in the value box
    * @param arg1 - holds value of quantity to to change to
    * @return nothing - void
    */
    void on_quantityBox_valueChanged(int arg1);

    /**
    * @brief generates list of customers for purchase view
    * @param &index - holds index of customer cell to be accessed in DB
    * @return nothing - void
    */
    void on_customerView_pressed(const QModelIndex &index);

    /**
    * @brief generates list of products for purchase view
    * @param &index - holds index of product cell to be accessed in DB
    * @return nothing - void
    */
    void on_productView_pressed(const QModelIndex &index);

private:
    Ui::purchase *ui;
    DbManager dbManager = DbManager("C:/Users/farna/documents/P2-Bulk-Club-Project/BulkClub.db");

    ///default value for id
    int id = -999;
    ///default value for name
    QString name = "Default";

    ///default value for type
    QString type = "Default";

    ///default value for product
    QString product = "Default";
    ///default value for quantity
    int quantity = -999;

    ///default value for price
    double price = -999;

};

#endif // PURCHASE_H
