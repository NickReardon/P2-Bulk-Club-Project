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

    int firstDateYear = tempDate.year();
    int firstDateMonth = tempDate.month();
    int firstDateDay = tempDate.month();

    int lastDateYear = tempDate.year();
    int lastDateMonth = tempDate.month();
    int lastDateDay = tempDate.day();


    switch(ui->ReportTypeDropdown->currentIndex())
    {
    case 0://daily
        break;

    case 1://weekly
        firstDateDay = (firstDateDay - tempDate.dayOfWeek());
        qDebug() << firstDateDay;
        lastDateDay = (lastDateDay + ( 7 - tempDate.dayOfWeek()));
        qDebug() << lastDateDay;
        break;
    case 2://monthly
        firstDateDay = 1;

        switch(tempDate.month())
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            lastDateDay = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            lastDateDay = 30;
            break;

        case 2:
            if(QDate::isLeapYear(tempDate.year()))
            {
                lastDateDay = 29;
            }
            else
            {
                lastDateDay = 28;
            }
            break;

        }
        break;

    case 3://yearly



        break;

    case 4://all time



        break;
    }


    dbManager.generateSalesReport(QDate(firstDateYear, firstDateMonth, firstDateDay),
                                  QDate(lastDateYear, lastDateMonth, lastDateDay),
                                  model);

    ui->SalesReportTable->setModel(model);
}

void adminPanel::on_salesReportCalendar_selectionChanged()
{
    tempDate = ui->salesReportCalendar->selectedDate();
    qDebug() << "Date changed: " << tempDate << endl;
}
