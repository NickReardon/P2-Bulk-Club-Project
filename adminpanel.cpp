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
}

adminPanel::~adminPanel()
{
    delete ui;
}
