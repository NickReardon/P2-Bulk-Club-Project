#include "adminpanel.h"
#include "ui_adminpanel.h"

adminPanel::adminPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminPanel)
{
    ui->setupUi(this);

    QSqlQueryModel* modal=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM purchases ORDER by id ASC");

    if(qry->exec())
    {
        modal->setQuery(*qry);

        ui->purchaseView->setModel(modal);
    }
    else
    {
        qDebug() << "fail!";
    }

    QSqlQueryModel* modal2=new QSqlQueryModel();

    QSqlQuery* qry2=new QSqlQuery();

    qry2->prepare("SELECT * FROM customers ORDER by id ASC");

    if(qry2->exec())
    {
        modal2->setQuery(*qry2);

        ui->memberView->setModel(modal2);
    }
    else
    {
        qDebug() << "fail!";
    }
}

adminPanel::~adminPanel()
{
    delete ui;
}

void adminPanel::on_logoutButton_clicked()
{
    hide();
}
