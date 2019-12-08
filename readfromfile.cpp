#include "readfromfile.h"
#include "ui_readfromfile.h"

readFromFile::readFromFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readFromFile)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->readFileButton->setEnabled(false);
}

readFromFile::~readFromFile()
{
    delete ui;
}

void readFromFile::on_openFileButton_released()
{
    QString tempFile = filename;
    filename = QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "Text files (*.txt)");

    if( !filename.isNull() )
    {

        qDebug() << "selected file path : " << filename.toUtf8();

        ui->filePathLabel->setText(filename);
        ui->progressBar->show();
        ui->readFileButton->setDisabled(false);
    }
    else
    {
        if( !tempFile.isNull() )
        {
            filename = tempFile;
            qDebug() << "selected file path : " << filename.toUtf8();

            ui->filePathLabel->setText(filename);
            ui->progressBar->show();
            ui->readFileButton->setDisabled(false);
        }
        else
        {
            ui->progressBar->hide();
            ui->filePathLabel->clear();
            ui->readFileButton->setEnabled(false);
        }
    }
}

void readFromFile::on_readFileButton_released()
{
    QString line;
    QFile inputFile(filename);
    qint64 fileSize = inputFile.size();
    double currentProgress = 0;

    qDebug() << fileSize;

    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            line = in.readLine();
            date = QDate::fromString(line, "MM/dd/yyyy");
            currentProgress += line.size() + 2;

            line = in.readLine();
            id = line.toInt();
            currentProgress += line.size() + 2;

            line = in.readLine();
            product = line;
            currentProgress += line.size() + 2;

            line = in.readLine();
            price = line.toDouble();
            currentProgress += line.size() + 2;

            line = in.readLine();
            quantity = line.toInt();
            currentProgress += line.size() + 2;

            QSqlQuery query;
            query.prepare("SELECT name, type FROM customers WHERE id = ( :id )");
            query.bindValue(":id", id);
            query.exec();
            query.next();
            qDebug() << query.lastError();
            name = query.value(0).toString();
            type = query.value(1).toString();

            dbManager.makePurchase(id, name, product, quantity, price, type, date);
            double revenue = QString::number( ((quantity * price) + (quantity * price * .0775)), 'f', 2).toDouble();
            dbManager.updateCustomerRevenue(id, revenue);
            dbManager.updateProductFromPurchase(product, quantity, revenue);

            qDebug() << (currentProgress);
            qDebug() << ((currentProgress/fileSize)*100);
            ui->progressBar->setValue((currentProgress/fileSize)*100);

        }
        inputFile.close();
        ui->progressBar->setValue(100);
        ui->readFileButton->setEnabled(false);
        qDebug() << "close file";
    }
}
