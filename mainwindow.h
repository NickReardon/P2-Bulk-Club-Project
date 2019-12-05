#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include "adminpanel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();

    void on_loginButton_clicked();

    void on_usernameEdit_returnPressed();

    void on_passwordEdit_returnPressed();

private:
    Ui::MainWindow *ui;

    DbManager dbManager = DbManager("C:/Users/farna/Documents/P2-Bulk-Club-Project/BulkClub.db");
};

#endif // MAINWINDOW_H
