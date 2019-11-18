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

    ui->salesReportCalendar->setSelectedDate(QDate::currentDate());
    tempDate = ui->salesReportCalendar->selectedDate();

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

void adminPanel::on_PrintReportButton_released()
{

}
