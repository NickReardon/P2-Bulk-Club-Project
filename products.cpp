#include "products.h"
#include "ui_products.h"

products::products(int t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::products)
{
    ui->setupUi(this);
    if(t == 1)
    {
        ui->varLabel->setText("Price:");
    }else if(t == 2)
    {
        ui->varLabel->hide();
        ui->varEdit->hide();
    }else
    {
        ui->varLabel->setText("Quantity:");
    }
}

products::~products()
{
    delete ui;
}

void products::on_okButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    QString str = ui->nameEdit->text();

       if(ui->varLabel->text() == "Price:")
       {
           QString str2 = ui->varEdit->text();
           query->prepare("INSERT INTO products (name, price, sold, revenue) VALUES (?,?,0,0)");
           query->addBindValue(str);
           query->addBindValue(str2);
           query->exec();

       }else if(ui->varLabel->text() == "Quantity:")
       {
           QSqlQuery valQry;
           valQry.prepare("SELECT * FROM products WHERE name = :n");
           valQry.bindValue(":n",str);
           valQry.exec();
           valQry.next();
           QString str2 = ui->varEdit->text();
           int qty = str2.toInt();
           qDebug() << valQry.value(0) << ' ' << valQry.value(1) << valQry.value(2) << endl;
           double rev = valQry.value(3).toDouble() + qty * valQry.value(1).toDouble();
           qty += valQry.value(2).toInt();
           query->prepare("UPDATE products SET (sold,revenue) = (:s,:r) WHERE name = :n");
           query->bindValue(":s",qty);
           query->bindValue(":r",rev);
           query->bindValue(":n",str);
           query->exec();
       }else
       {
           query->prepare("DELETE FROM products WHERE name = ?");
           query->addBindValue(str);
           query->exec();

       }
       close();
}

void products::on_cancelButton_clicked()
{
    close();
}
