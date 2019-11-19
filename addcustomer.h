#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class addCustomer;
}

class addCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit addCustomer(QWidget *parent = nullptr);
    ~addCustomer();

private slots:
    void on_cancelCustomerButton_clicked();

    void on_addCustomerButton_clicked();

private:
    Ui::addCustomer *ui;
    DbManager dbManager = DbManager("C:/Users/Nox/Documents/P2-Bulk-Club-Project/BulkClub.db");
};

#endif // ADDCUSTOMER_H
