#include "purchase.h"
#include "ui_purchase.h"

purchase::purchase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::purchase)
{
    ui->setupUi(this);

    QSqlQueryModel* modal=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT id, name, type FROM customers ORDER by id ASC");

    if(qry->exec())
    {
        modal->setQuery(*qry);

        ui->customerView->setModel(modal);
        ui->customerView->hideColumn(2);
        ui->customerView->setColumnWidth(0, 50);
        ui->customerView->setColumnWidth(1, 190);
    }
    else
    {
        qDebug() << "fail!";
    }


    QSqlQuery query("SELECT name, price FROM products");\
    query.exec();

    QSqlQueryModel *productListModel = new QSqlQueryModel;
    productListModel->setQuery(query);

    ui->productView->setModel(productListModel);
    ui->productView->setColumnWidth(0, 150);
    ui->productView->setColumnWidth(1, 60);
    ui->purchaseButton->setEnabled(false);

}

purchase::~purchase()
{
    delete ui;
}


void purchase::on_purchaseButton_released()
{
    dbManager.makePurchase(id, name, product, quantity, price, type);
    double revenue = QString::number( ((quantity * price) + (quantity * price * .0775)), 'f', 2).toDouble();
    qDebug() << revenue;
    dbManager.updateCustomerRevenue(id, revenue);
    dbManager.updateProductFromPurchase(product, quantity, revenue);
    close();
}

void purchase::on_quantityBox_valueChanged(int arg1)
{
    quantity = arg1;

    if(id > 0 && product != "Default")
    {
        ui->purchaseButton->setDisabled(false);
    }
}

void purchase::on_customerView_pressed(const QModelIndex &index)
{
    name = index.siblingAtColumn(1).data().toString();
    qDebug() << name;
    id = index.siblingAtColumn(0).data().toInt();
    qDebug() << id;
    type = index.siblingAtColumn(2).data().toString();
    qDebug() << type;
    if(quantity > 0 && product != "Default")
    {
        ui->purchaseButton->setDisabled(false);
    }
}

void purchase::on_productView_pressed(const QModelIndex &index)
{
    product = index.siblingAtColumn(0).data().toString();
    price = index.siblingAtColumn(1).data().toDouble();

    if(quantity > 0 && name != "Default")
    {
        ui->purchaseButton->setDisabled(false);
    }
}
