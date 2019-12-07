#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include "dbmanager.h"
#include "addcustomer.h"
#include "confirmupdate.h"
#include "purchase.h"

namespace Ui {
class adminPanel;
}

class adminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit adminPanel(QWidget *parent = nullptr);
    ~adminPanel();

    void updateReportProductView();

    void updateTotalLabel();

    void updateReportMemberView();

    void updateReport();

    void update_ReportRegularMembeCount();

    void update_ReportExecutiveMemberCount();

    void updatePurchases();
    
    void updateCustomers();
    
    void updateProducts();
    
private slots:
    void on_logoutButton_clicked();

    void on_addCustomerButton_clicked();

    void on_GenerateReportButton_released();

    void on_salesReportCalendar_clicked(const QDate &date);

    void on_salesReportCalendar_selectionChanged();

    void on_productAdd_clicked();

    void on_productDel_clicked();

    void on_testButton_clicked();

    void on_productSearch_editingFinished();

    void on_removeCustomerButton_clicked();

    void on_upgradeCustomer_clicked();

    void on_ReportProductView_activated(const QModelIndex &index);

    void on_ReportMemberView_pressed(const QModelIndex &index);

    void on_ReportProductView_pressed(const QModelIndex &index);

private:
    Ui::adminPanel *ui;
    DbManager dbManager = DbManager("C:/Users/Nick/source/repos/P2-Bulk-Club-Project/BulkClub.db");

    QDate tempDate;
    QDate firstDate;
    QDate endDate;
};

#endif // ADMINPANEL_H
