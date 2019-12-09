#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui
{
class products;
}

class products : public QDialog
{
    Q_OBJECT

public:
    explicit products(int t, QWidget *parent = nullptr);
    ~products();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::products *ui;

    DbManager dbManager = DbManager("C:/Users/farna/documents/P2-Bulk-Club-Project/BulkClub.db");
};


#endif // PRODUCTS_H
