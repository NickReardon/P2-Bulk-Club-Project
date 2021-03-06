#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "products.h"
#include "readfromfile.h"


adminPanel::adminPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminPanel)
{
    ui->setupUi(this);

    updatePurchases();

    updateCustomers();
    updateProducts();
    totalView();
}

adminPanel::~adminPanel()
{
    delete ui;
}

void adminPanel::updatePurchases()
{
    QSqlQueryModel* modal=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM purchases ORDER by id ASC");

    if(qry->exec())
    {
        modal->setQuery(*qry);

        ui->purchaseView->setModel(modal);
        ui->purchaseView->setColumnWidth(0, 40);
        ui->purchaseView->setColumnWidth(1, 155);
        ui->purchaseView->setColumnWidth(3, 170);
        ui->purchaseView->setColumnWidth(7, 70);
    }
    else
    {
        qDebug() << "fail!";
    }
}

void adminPanel::totalView()
{
    QSqlQueryModel* modal3=new QSqlQueryModel();

    QSqlQuery* qry3=new QSqlQuery();

    qry3->prepare("SELECT SUM(total) From purchases");

    if(qry3->exec())
    {
        modal3->setQuery(*qry3);

        ui->totalView->setModel(modal3);
    }
    else
    {
        qDebug() << "fail!";
    }
}

void adminPanel::updateCustomers()
{
    QSqlQueryModel* modal2=new QSqlQueryModel();

    QSqlQuery* qry2=new QSqlQuery();

    qry2->prepare("SELECT * FROM customers ORDER by id ASC");

    if(qry2->exec())
    {
        modal2->setQuery(*qry2);

        ui->memberView->setModel(modal2);
        ui->memberView->setColumnWidth(1, 155);
    }
    else
    {
        qDebug() << "fail!";
    }
}

void adminPanel::updateProducts()
{
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

void adminPanel::on_logoutButton_clicked()
{
    close();
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

void adminPanel::updateReportProductView()
{
    QSqlQuery query;

    switch(ui->ReportMemberTypeDropdown->currentIndex())
    {
    case 0:
        query.prepare("SELECT DISTINCT product FROM purchases WHERE date >= (:start) AND date <= (:end) ORDER by name ASC");
        break;

    case 1:
        query.prepare("SELECT DISTINCT product FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'regular' ORDER by name ASC");
        break;

    case 2:
        query.prepare("SELECT DISTINCT product FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'executive' ORDER by name ASC" );
        break;
    }


    query.bindValue(":start", firstDate);
    query.bindValue(":end", endDate);
    query.exec();

    QSqlQueryModel *productListModel = new QSqlQueryModel;
    productListModel->setQuery(query);

    ui->ReportProductView->setModel(productListModel);
    ui->ReportProductView->setColumnWidth(0, 130);
}

void adminPanel::updateTotalLabel()
{


    double total;

    QSqlQuery query;

    switch(ui->ReportMemberTypeDropdown->currentIndex())
    {
    case 0:
        query.prepare("SELECT SUM(total) FROM purchases WHERE date >= (:start) AND date <= (:end)");
        break;

    case 1:
        query.prepare("SELECT SUM(total) FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'regular'");
        break;

    case 2:
        query.prepare("SELECT SUM(total) FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'executive'" );
        break;
    }

    query.bindValue(":start", firstDate);
    query.bindValue(":end", endDate);
    query.exec();
    query.next();

    total = query.record().value(0).toDouble();

    ui->ReportTotalLabel->setText("Report Total Revenue: $ " + QString::number(total));
}

void adminPanel::updateReportMemberView()
{
    QSqlQuery query;
    switch(ui->ReportMemberTypeDropdown->currentIndex())
    {
    case 0:
        query.prepare("SELECT DISTINCT id, name FROM purchases WHERE date >= (:start) AND date <= (:end) ORDER by id ASC");
        break;

    case 1:
        query.prepare("SELECT DISTINCT id, name FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'regular' ORDER by id ASC");
        break;

    case 2:
        query.prepare("SELECT DISTINCT id, name FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'executive' ORDER by id ASC" );
        break;
    }
    query.bindValue(":start", firstDate);
    query.bindValue(":end", endDate);
    query.exec();

    QSqlQueryModel *memberList = new QSqlQueryModel;
    memberList->setQuery(query);

    ui->ReportMemberView->setModel(memberList);
    ui->ReportMemberView->setColumnWidth(0, 40);
    ui->ReportMemberView->setColumnWidth(1, 92);
}

void adminPanel::updateReport()
{
    QSqlQuery query;
    switch(ui->ReportMemberTypeDropdown->currentIndex())
    {
    case 0:
        query.prepare("SELECT * FROM purchases WHERE date >= (:start) AND date <= (:end) ORDER by date ASC, time ASC");
        break;

    case 1:
        query.prepare("SELECT * FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'regular' ORDER by date ASC, time ASC");
        break;

    case 2:
        query.prepare("SELECT * FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'executive' ORDER by date ASC, time ASC" );
        break;
    }
    query.bindValue(":start", firstDate);
    query.bindValue(":end", endDate);
    query.exec();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    ui->SalesReportTable->setModel(model);
    ui->SalesReportTable->setColumnWidth(0, 40);
    ui->SalesReportTable->setColumnWidth(1, 145);
    ui->SalesReportTable->setColumnWidth(2, 60);
    ui->SalesReportTable->setColumnWidth(3, 150);
    ui->SalesReportTable->setColumnWidth(4, 55);
    ui->SalesReportTable->setColumnWidth(5, 40);
    ui->SalesReportTable->setColumnWidth(6, 58);
    ui->SalesReportTable->setColumnWidth(7, 70);
    ui->SalesReportTable->setColumnWidth(8, 60);
}

void adminPanel::update_ReportRegularMembeCount()
{
    int count;

    QSqlQuery query;
    query.prepare("SELECT count(DISTINCT id) FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'regular'");
    query.bindValue(":start", firstDate);
    query.bindValue(":end", endDate);
    query.exec();
    query.next();

    count = query.value(0).toInt();

    ui->ReportRegularCount->setText("Regular members: " + QString::number(count));
}

void adminPanel::update_ReportExecutiveMemberCount()
{
    int count;

    QSqlQuery query;
    query.prepare("SELECT count(DISTINCT id) FROM purchases WHERE date >= (:start) AND date <= (:end) AND type = 'executive'");
    query.bindValue(":start", firstDate);
    query.bindValue(":end", endDate);
    query.exec();
    query.next();

    count = query.value(0).toInt();
    ui->ReportExecutiveCount->setText("Executive members: " + QString::number(count));
}

void adminPanel::on_GenerateReportButton_released()
{
    //QSqlQueryModel *model = new QSqlQueryModel;

    firstDate = tempDate;

    endDate = tempDate;

    switch(ui->ReportTypeDropdown->currentIndex())
    {
    case 0://daily
        break;

    case 1://weekly
        if(tempDate.dayOfWeek() == 7)
        {
            firstDate = firstDate.addDays( 0 - ( 7 - firstDate.dayOfWeek()));
            endDate = endDate.addDays( 0 - ( 1 - endDate.dayOfWeek()));
        }
        else
        {
            firstDate = firstDate.addDays( 0 - firstDate.dayOfWeek());
            endDate = endDate.addDays( 6 - endDate.dayOfWeek());
        }

        break;
    case 2://monthly
        firstDate.setDate(firstDate.year(), firstDate.month(), 1);

        endDate.setDate(endDate.year(), endDate.month(), endDate.daysInMonth());
        break;

    case 3://yearly
        firstDate.setDate(firstDate.year(), 1, 1);


        endDate.setDate(endDate.year(), 12, 31);


        break;

    case 4://all time
        firstDate.setDate(1900, 1, 1);

        endDate.setDate(2999, 12, 31);

        break;
    }




    qDebug() << firstDate << endDate;

    updateReport();

    updateTotalLabel();

    updateReportProductView();

    updateReportMemberView();

    update_ReportRegularMembeCount();

    update_ReportExecutiveMemberCount();

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
    purchase page;
    page.setModal(true);
    page.exec();

    dbManager.reOpen();
    QSqlQueryModel* modal=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM products ORDER by name ASC");
    if(qry->exec())
    {
        modal->setQuery(*qry);
        ui->productView->setModel(modal);
    }

    updateCustomers();
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
        ui->removeEdit->setPlaceholderText("Name/ID Doesn't Exists!");
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

void adminPanel::on_ReportProductView_activated(const QModelIndex &index)
{
    QSqlQuery query;
    query.prepare("SELECT SUM(quantity) FROM purchases WHERE date >= (:start) AND date <= (:end) AND product = (:product)");
    query.bindValue(":product", index.data().toString());
    query.bindValue(":start", firstDate);
    query.bindValue(":end", endDate);
    query.exec();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,"Total Quntity");
    ui->ReportProductQuantity->setModel(model);
    ui->ReportProductQuantity->setColumnWidth(0, 130);

}

void adminPanel::on_ReportMemberView_pressed(const QModelIndex &index)
{
    QSqlQuery query;
    query.prepare("SELECT product, quantity, price, total FROM purchases WHERE date >= (:start) AND date <= (:end) AND id = (:id)  ORDER by date ASC, time ASC");
    query.bindValue(":id", index.siblingAtColumn(0).data().toInt());
    query.bindValue(":start", firstDate);
    query.bindValue(":end", endDate);
    query.exec();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    ui->ReportProductMemberPurchases->setModel(model);
    ui->ReportProductMemberPurchases->setColumnWidth(1, 55);
    ui->ReportProductMemberPurchases->setColumnWidth(2, 40);
    ui->ReportProductMemberPurchases->setColumnWidth(3, 40);
}

void adminPanel::on_ReportProductView_pressed(const QModelIndex &index)
{
    on_ReportProductView_activated(index);
}

void adminPanel::on_readFromFileButton_released()
{
    readFromFile fileOpen;
    fileOpen.setModal(true);
    fileOpen.exec();
}

void adminPanel::on_showallButton_clicked()
{
    totalView();
    updatePurchases();
    ui->purchaseSearch->setText("");
    ui->purchaseSearch->setPlaceholderText("Enter Name or ID");
}

void adminPanel::on_showallProducts_clicked()
{
    updateProducts();
    ui->productSearch->setText("");
    ui->productSearch->setPlaceholderText("Product name");
}

void adminPanel::on_productSearch_returnPressed()
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

    }else if(dbManager.productExists(str))
    {
        qry->prepare("SELECT * FROM products WHERE name = :n");
        qry->bindValue(":n",str);
        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->productView->setModel(modal);
        }
    }
    else
    {
        ui->productSearch->setText("");
        ui->productSearch->setPlaceholderText("Product Doesn't Exists!");
    }
}

void adminPanel::on_purchaseSearch_returnPressed()
{
    QString str = ui->purchaseSearch->text();

    dbManager.reOpen();
    QSqlQueryModel* modal=new QSqlQueryModel();
    QSqlQuery *qry=new QSqlQuery();

    if(str == "")
    {
        totalView();
        updatePurchases();

    }else if(dbManager.nameExists(str))
    {
        qry->prepare("SELECT SUM(total) From customers Where name = (:nm)");
        qry->bindValue(":nm",str);
        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->totalView->setModel(modal);
        }

        QSqlQueryModel* modal=new QSqlQueryModel();

        QSqlQuery* qry=new QSqlQuery();

        qry->prepare("SELECT * FROM purchases WHERE name = (:nm) ORDER by date ASC");
        qry->bindValue(":nm", str);
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
    else if(dbManager.idExists(str))
    {
        qry->prepare("SELECT SUM(total) From customers Where id = (:nm)");
        qry->bindValue(":nm",str);
        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->totalView->setModel(modal);
        }

        QSqlQueryModel* modal=new QSqlQueryModel();

        QSqlQuery* qry=new QSqlQuery();

        qry->prepare("SELECT * FROM purchases WHERE id = (:nm) ORDER by date ASC");
        qry->bindValue(":nm", str);
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
    else
    {
        ui->purchaseSearch->setText("");
        ui->purchaseSearch->setPlaceholderText("Name/ID doesn't EXIST!");
    }
}

void adminPanel::on_expireButton_released()
{
    QDate expire(ui->yearBox->value(), ui->monthBox->value(),1);

    qDebug() << expire;

    QSqlQueryModel* modal=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM customers WHERE expire >= (:e) AND expire <= (:b)");
    qry->bindValue(":e", expire.toString("yyyy-MM-dd"));
    expire = QDate(expire.year(),expire.month(), expire.daysInMonth());
    qry->bindValue(":b", expire.toString("yyyy-MM-dd"));

    qDebug() << expire;

    if(qry->exec())
    {
        modal->setQuery(*qry);

        expireDisplay window2(this,modal);
        window2.setModal(true);
        window2.exec();

        dbManager.reOpen();
    }
    else
    {
        qDebug() << "fail!";
    }
}

void adminPanel::on_showBox_currentIndexChanged(int index)
{

    QSqlQueryModel* modal=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    switch (index)
    {
        case 0 :  qry->prepare("SELECT * FROM customers ORDER by id ASC");

            break;

        case 1 :  qry->prepare("SELECT * FROM customers WHERE type = 'executive' ORDER by id ASC");

            break;

        case 2 :  qry->prepare("SELECT * FROM customers WHERE type = 'regular' ORDER by id ASC");

            break;
    }

    if(qry->exec())
    {
        modal->setQuery(*qry);

        ui->memberView->setModel(modal);
        ui->memberView->setColumnWidth(1, 155);
    }
    else
    {
        qDebug() << "fail!";
    }
}
