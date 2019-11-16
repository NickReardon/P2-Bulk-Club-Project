#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include "dbmanager.h"

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

private:
    Ui::adminPanel *ui;
    DbManager dbManager = DbManager("C:/Users/farna/Documents/P2-Bulk-Club-Project/BulkClub.db");
};

#endif // ADMINPANEL_H
