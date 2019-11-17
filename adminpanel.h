#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include "dbmanager.h"
#include "addcustomer.h"

namespace Ui {
class adminPanel;
}

class adminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit adminPanel(QWidget *parent = nullptr);
    ~adminPanel();

private slots:
    void on_logoutButton_clicked();

    void on_addCustomerButton_clicked();

    void on_GenerateReportButton_released();

    void on_salesReportCalendar_selectionChanged();

private:
    Ui::adminPanel *ui;
    DbManager dbManager = DbManager("C:/Users/Nick/source/repos/P2-Bulk-Club-Project/BulkClub.db");

    QDate tempDate;
};

#endif // ADMINPANEL_H
