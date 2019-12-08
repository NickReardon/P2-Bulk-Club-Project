#include "addcustomer.h"
#include "ui_addcustomer.h"
/**
 * @file
 */


/**
 * @brief Constructor
 *
 * Constructor sets up ui for addCustomer
 * @param *parent - for QDialog
 */
 */
addCustomer::addCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCustomer)
{
    ui->setupUi(this);
}

/**
 * @brief Destructor
 *
 * Close the addCustomer UI
 */
addCustomer::~addCustomer()
{
    delete ui;
}

/**
 * @brief cancels addCustomer execution and closes UI
 * @return nothing - void
 */
void addCustomer::on_cancelCustomerButton_clicked()
{
    hide();
}

/**
 * @brief on user click, validates all data input for user data values and adds to DB
 * @return nothing - void
 *
 */
void addCustomer::on_addCustomerButton_clicked()
{
    bool success = false;

    if(ui->idEdit->text() == "")
    {
       ui->idEdit->setPlaceholderText("Member Id EMPTY!");
       success = true;
    }

    if(ui->nameEdit->text() == "")
    {
        ui->nameEdit->setPlaceholderText("Name EMPTY!");
        success = true;
    }

    if(ui->typeEdit->text() == "")
    {
        ui->typeEdit->setPlaceholderText("Type EMPTY!");
        success = true;
    }

    if(ui->expirationEdit->text() == "")
    {
        ui->expirationEdit->setPlaceholderText("Expiration EMPTY!");
        success = true;
    }

    if(dbManager.nameExists(ui->nameEdit->text()))
    {
        ui->nameEdit->setText("");
        ui->nameEdit->setPlaceholderText("Use different name!");
        success = true;
    }

    if(!success)
    {
        dbManager.addAccount(ui->idEdit->text(), ui->nameEdit->text(), ui->expirationEdit->text(), ui->typeEdit->text());
        hide();
    }

}
