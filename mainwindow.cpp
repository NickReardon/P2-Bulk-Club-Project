#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Nick/source/repos/P2-Bulk-Club-Project/SAND.png");
    ui->picLabel->setPixmap(pix);

    //test
}

MainWindow::~MainWindow()
{
    delete ui;
}
