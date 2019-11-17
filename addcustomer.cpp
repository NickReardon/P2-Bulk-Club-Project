#include "addcustomer.h"
#include "ui_addcustomer.h"

addCustomer::addCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCustomer)
{
    ui->setupUi(this);
}

addCustomer::~addCustomer()
{
    delete ui;
}

void addCustomer::on_cancelCustomerButton_clicked()
{
    hide();
}

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
        ui->typeEdit->setPlaceholderText("Membership Type EMPTY!");
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
        ui->nameEdit->setPlaceholderText("Choose a different name!");
        success = true;
    }
}
