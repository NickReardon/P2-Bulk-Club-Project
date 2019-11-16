#include "adminpanel.h"
#include "ui_adminpanel.h"

adminPanel::adminPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminPanel)
{
    ui->setupUi(this);
}

adminPanel::~adminPanel()
{
    delete ui;
}
