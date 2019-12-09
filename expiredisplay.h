#ifndef EXPIREDISPLAY_H
#define EXPIREDISPLAY_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class expireDisplay;
}

class expireDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit expireDisplay(QWidget *parent, QSqlQueryModel *df);
    ~expireDisplay();

private:
    Ui::expireDisplay *ui;
};

#endif // EXPIREDISPLAY_H
