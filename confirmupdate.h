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

private:
    Ui::confirmUpdate *ui;
    DbManager dbManager = DbManager("C:/Users/farna/Documents/P2-Bulk-Club-Project/BulkClub.db");
};

#endif // CONFIRMUPDATE_H
