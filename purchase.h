#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui
{
    class purchase;
}

class purchase : public QDialog
{
    Q_OBJECT

public:
    explicit purchase(QWidget *parent = nullptr);
    ~purchase();

private slots:

    void on_purchaseButton_released();

    void on_quantityBox_valueChanged(int arg1);

    void on_customerView_pressed(const QModelIndex &index);

    void on_productView_pressed(const QModelIndex &index);

private:
    Ui::purchase *ui;
    DbManager dbManager = DbManager("C:/Users/farna/documents/P2-Bulk-Club-Project/BulkClub.db");

    int id = -999;
    QString name = "Default";
    QString type = "Default";
    QString product = "Default";
    int quantity = -999;
    double price = -999;

};

#endif // PURCHASE_H
