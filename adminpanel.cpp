#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "products.h"

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
    QSqlQueryModel* modal3=new QSqlQueryModel();

    QSqlQuery* qry3=new QSqlQuery();

    qry3->prepare("SELECT * FROM products ORDER by name ASC");

    if(qry3->exec())
    {
        modal3->setQuery(*qry3);

        ui->productView->setModel(modal3);
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

void adminPanel::on_addCustomerButton_clicked()
{
    addCustomer window2;
    window2.setModal(true);
    window2.exec();

    dbManager.reOpen();

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

void adminPanel::on_GenerateReportButton_released()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    QDate firstDate = tempDate;

    QDate lastDate = tempDate;



    switch(ui->ReportTypeDropdown->currentIndex())
    {
    case 0://daily
        break;

    case 1://weekly
        if(tempDate.dayOfWeek() == 7)
        {
            firstDate = firstDate.addDays( 0 - ( 7 - firstDate.dayOfWeek()));
            lastDate = lastDate.addDays( 0 - ( 1 - lastDate.dayOfWeek()));
        }
        else
        {
            firstDate = firstDate.addDays( 0 - firstDate.dayOfWeek());
            lastDate = lastDate.addDays( 6 - lastDate.dayOfWeek());
        }

        break;
    case 2://monthly
        firstDate.setDate(firstDate.year(), firstDate.month(), 1);

        lastDate.setDate(lastDate.year(), lastDate.month(), lastDate.daysInMonth());
        break;

    case 3://yearly
        firstDate.setDate(firstDate.year(), 1, 1);


        lastDate.setDate(lastDate.year(), 12, 31);


        break;

    case 4://all time
        firstDate.setDate(1900, 1, 1);

        lastDate.setDate(2999, 12, 31);

        break;
    }




    qDebug() << firstDate << lastDate;
    dbManager.generateSalesReport(firstDate, lastDate, model);

    ui->SalesReportTable->setModel(model);
}

void adminPanel::on_salesReportCalendar_selectionChanged()
{
    tempDate = ui->salesReportCalendar->selectedDate();
    qDebug() << "Date changed: " << tempDate << endl;
}

void adminPanel::on_salesReportCalendar_clicked(const QDate &date)
{
    tempDate = date;
    qDebug() << "Date changed: " << tempDate << endl;
}


void adminPanel::on_productAdd_clicked()
{
    products insertProduct(1);
    insertProduct.setModal(true);
    insertProduct.exec();

    dbManager.reOpen();
    QSqlQueryModel* modal=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM products ORDER by name ASC");
    if(qry->exec())
    {
        modal->setQuery(*qry);
        ui->productView->setModel(modal);
    }
}

void adminPanel::on_productDel_clicked()
{
    products delProduct(2);
    delProduct.setModal(true);
    delProduct.exec();

    dbManager.reOpen();
    QSqlQueryModel* modal=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM products ORDER by name ASC");
    if(qry->exec())
    {
        modal->setQuery(*qry);
        ui->productView->setModel(modal);
    }
}

void adminPanel::on_testButton_clicked()
{
    products purProduct(3);
    purProduct.setModal(true);
    purProduct.exec();

    dbManager.reOpen();
    QSqlQueryModel* modal=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM products ORDER by name ASC");
    if(qry->exec())
    {
        modal->setQuery(*qry);
        ui->productView->setModel(modal);
    }
}

void adminPanel::on_productSearch_editingFinished()
{
    QString str = ui->productSearch->text();

    dbManager.reOpen();
    QSqlQueryModel* modal=new QSqlQueryModel();
    QSqlQuery *qry=new QSqlQuery();

    if(str == "")
    {
        qry->prepare("SELECT * FROM products ORDER by name ASC");
        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->productView->setModel(modal);
        }

    }else
    {
        qry->prepare("SELECT * FROM products WHERE name = :n");
        qry->bindValue(":n",str);
        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->productView->setModel(modal);
        }
    }
}

void adminPanel::on_removeCustomerButton_clicked()
{
    bool success = false;

    if(ui->removeEdit->text() == "")
    {
        ui->removeEdit->setPlaceholderText("Name or ID EMPTY!");
        success = true;
    }

    else if(!dbManager.nameExists(ui->removeEdit->text()) && !dbManager.idExists(ui->removeEdit->text()))
    {
        ui->removeEdit->setText("");
        ui->removeEdit->setPlaceholderText("Name Doesn't Exists!");
        success = true;
    }

    if(!success && dbManager.nameExists(ui->removeEdit->text()))
    {
        dbManager.removeCustomer(ui->removeEdit->text());
        ui->removeEdit->setText("");
    }
    else if(!success && dbManager.idExists(ui->removeEdit->text()))
    {
        dbManager.removeCustomerId(ui->removeEdit->text());
        ui->removeEdit->setText("");
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

void adminPanel::on_upgradeCustomer_clicked()
{
    confirmUpdate window2;
    window2.setModal(true);
    window2.exec();

    dbManager.reOpen();
}
