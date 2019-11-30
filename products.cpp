#include "products.h"
#include "ui_products.h"

products::products(int t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::products)
{
    ui->setupUi(this);
    if(t == 1)
    {
        ui->varEdit->hide();
        ui->varLabel->setText("Price:");
    }else if(t == 2)
    {
        ui->varLabel->hide();
        ui->varEdit->hide();
        ui->dVarEdit->hide();
    }else
    {
        ui->dVarEdit->hide();
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
           if(dbManager.productExists(str) or str == "")
           {
               ui->nameEdit->setText("Invalid");
           }else
           {
               query->prepare("INSERT INTO products (name, price, sold, revenue) VALUES (?,?,0,0)");
               query->addBindValue(str);
               query->addBindValue(ui->dVarEdit->value());
               query->exec();
               close();
           }

       }else if(ui->varLabel->text() == "Quantity:")
       {
           if(ui->varEdit->value()==0)
           {
               ui->nameEdit->setText("Invalid");

           }else if(dbManager.productExists(str))
           {
               QSqlQuery valQry;
               valQry.prepare("SELECT * FROM products WHERE name = :n");
               valQry.bindValue(":n",str);
               valQry.exec();
               valQry.next();

               qDebug() << valQry.value(0) << ' ' << valQry.value(1) << valQry.value(2) << endl;
               int qty = ui->varEdit->value();
               double rev = valQry.value(3).toDouble() + qty * valQry.value(1).toDouble();
               qty += valQry.value(2).toInt();
               query->prepare("UPDATE products SET (sold,revenue) = (:s,:r) WHERE name = :n");
               query->bindValue(":s",qty);
               query->bindValue(":r",rev);
               query->bindValue(":n",str);
               query->exec();

               rev = ui->varEdit->value() * valQry.value(1).toDouble();

               QDate d = QDate::currentDate();
               QTime t = QTime::currentTime();
               query->prepare("INSERT INTO purchases (number,id,product,quantity,price,total,date,time,dayNumber,monthNumber,yearNumber) VALUES (:num,:id,:name,:qty,:price,:total,:date,:time,:day,:month,:year)");
               query->bindValue(":num","0");
               query->bindValue(":id","0");
               query->bindValue(":name",str);
               query->bindValue(":qty",ui->varEdit->value());
               query->bindValue(":price",valQry.value(1));
               query->bindValue(":total",rev);
               query->bindValue(":date",d);
               query->bindValue(":time",t);
               query->bindValue(":day",d.day());
               query->bindValue(":month",d.month());
               query->bindValue(":year",d.year());
               query->exec();
               close();
           }else
           {
               ui->nameEdit->setText("Not Found");
           }

       }else
       {
           if(dbManager.productExists(str))
           {
               query->prepare("DELETE FROM products WHERE name = ?");
               query->addBindValue(str);
               query->exec();
               close();
           }else
           {
               ui->nameEdit->setText("Not Found");
           }


       }
}

void products::on_cancelButton_clicked()
{
    close();
}
