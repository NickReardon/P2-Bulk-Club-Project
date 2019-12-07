#include "confirmupdate.h"
#include "ui_confirmupdate.h"

confirmUpdate::confirmUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmUpdate)
{
    ui->setupUi(this);
}

confirmUpdate::~confirmUpdate()
{
    delete ui;
}

void confirmUpdate::on_cancelButton_clicked()
{
    hide();
}

void confirmUpdate::on_upgradeButton_clicked()
{
    bool success = false;

    if(ui->nameEdit->text() == "" && ui->idEdit->text() == "")
    {
           ui->nameEdit->setPlaceholderText("Name EMPTY!");
           ui->idEdit->setPlaceholderText("ID EMPTY!");
           success = true;
    }


        if(!dbManager.nameExists(ui->nameEdit->text()) && ui->nameEdit->text() != "")
        {
            ui->nameEdit->setText("");
            ui->nameEdit->setPlaceholderText("Name doesn't EXIST");
            success = true;
        }

        if(!dbManager.idExists(ui->idEdit->text()) && ui->idEdit->text() != "")
        {
            ui->idEdit->setText("");
            ui->idEdit->setPlaceholderText("ID doesn't EXIST");
            success = true;
        }


    if(!success && dbManager.nameExists(ui->nameEdit->text()))
    {
        dbManager.updateAccount("executive",ui->nameEdit->text());
        hide();
    }

    if(!success && dbManager.idExists(ui->idEdit->text()))
    {
        dbManager.updateAccount("executive", ui->idEdit->text());
        hide();
    }

}

void confirmUpdate::on_downgradeButton_clicked()
{
    bool success = false;

    if(ui->nameEdit->text() == "" && ui->idEdit->text() == "")
    {
           ui->nameEdit->setPlaceholderText("Name EMPTY!");
           ui->idEdit->setPlaceholderText("ID EMPTY!");
           success = true;
    }


        if(!dbManager.nameExists(ui->nameEdit->text()) && ui->nameEdit->text() != "")
        {
            ui->nameEdit->setText("");
            ui->nameEdit->setPlaceholderText("Name doesn't EXIST");
            success = true;
        }

        if(!dbManager.idExists(ui->idEdit->text()) && ui->idEdit->text() != "")
        {
            ui->idEdit->setText("");
            ui->idEdit->setPlaceholderText("ID doesn't EXIST");
            success = true;
        }


    if(!success && dbManager.nameExists(ui->nameEdit->text()))
    {
        dbManager.updateAccount("regular",ui->nameEdit->text());
        hide();
    }

    if(!success && dbManager.idExists(ui->idEdit->text()))
    {
        dbManager.updateAccount("regular", ui->idEdit->text());
        hide();
    }
}
