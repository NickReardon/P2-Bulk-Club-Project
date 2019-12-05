#include "confirmupdate.h"
#include "ui_confirmupdate.h"

confirmUpdate::confirmUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmUpdate)
{
    ui->setupUi(this);
}

confirmUpdate::~confirmUpdate()
{
    delete ui;
}
