#include "expiredisplay.h"
#include "ui_expiredisplay.h"

expireDisplay::expireDisplay(QWidget *parent, QSqlQueryModel *df) :
    QDialog(parent),
    ui(new Ui::expireDisplay)
{
    ui->setupUi(this);
    ui->expireView->setModel(df);
}

expireDisplay::~expireDisplay()
{
    delete ui;
}
