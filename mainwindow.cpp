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

void MainWindow::on_clearButton_clicked()
{
    ui->passwordEdit->clear();
    ui->usernameEdit->clear();
}

void MainWindow::on_loginButton_clicked()
{
    ui->invalidLabel->setText("");
        QString password;

        QString usernameInput = ui->usernameEdit->text();
        QString passwordInput = ui->passwordEdit->text();

        password = dbManager.GetPassword(usernameInput);
        if(passwordInput == password)
        {
            if(!dbManager.CheckAdmin(usernameInput))
            {
                ui->invalidLabel->setText("");

                /*
                hide();

                Products products(this, usernameInput);
                products.setModal(true);
                products.exec();

                show();
                */
            }
            else
            {
                ui->invalidLabel->setText("");

                hide();

                adminPanel admin;
                admin.setModal(true);
                admin.exec();

                show();
            }
        }
        else
        {
            ui->invalidLabel->setText("Invalid username or password");
        }

        dbManager.reOpen();
}
