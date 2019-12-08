#ifndef CONFIRMUPDATE_H
#define CONFIRMUPDATE_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class confirmUpdate;
}

class confirmUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit confirmUpdate(QWidget *parent = nullptr);
    ~confirmUpdate();

private slots:
    void on_cancelButton_clicked();

    void on_upgradeButton_clicked();

    void on_downgradeButton_clicked();

private:
    Ui::confirmUpdate *ui;
    DbManager dbManager = DbManager("C:/Users/Nick/source/repos/P2-Bulk-Club-Project/BulkClub.db");
};

#endif // CONFIRMUPDATE_H
