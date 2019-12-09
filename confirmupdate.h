#ifndef CONFIRMUPDATE_H
#define CONFIRMUPDATE_H

#include <QDialog>
#include "dbmanager.h"
/**
 * @file
 */


/**
 * \class confirmUpdate
 *
 * \brief class for validating and confirming an upgrade or a downgrade for a customers membership type
 *
 * confirmUpdate prompts a UI for an admin to enter a name or an id and either Upgrade its membership type or downgrade its membership
 * type from executive to regular.
 */

namespace Ui {
class confirmUpdate;
}

class confirmUpdate : public QDialog
{
    Q_OBJECT

public:
    /**
   * @brief Constructor
   *
   * Constructor , initializes ui for changing a customers membership type
   * @param *parent - for QDialog
   */
    explicit confirmUpdate(QWidget *parent = nullptr);
    /**
   * @brief Destructor
   *
   * Closes UI upon requested exit
   */
    ~confirmUpdate();

private slots:
    /**
     * @brief upon user click, exits Upgrade UI and cancels operations
     * @return void - nothing
     */
    void on_cancelButton_clicked();

    /**
    * @brief upon user click, verifies input of data fields and verifies it exists in DB
    * , if verification successful, succesfully upgrades customer membership value to executive
    * @return void - nothing
    */
    void on_upgradeButton_clicked();

    /**
     * @brief upon user click, verifies input of data fields and verifies it exists in DB
     * , if verification successful, succesfully downgrades customer membership value to regular
     * @return void - nothing
     */
    void on_downgradeButton_clicked();

private:
    Ui::confirmUpdate *ui;
    DbManager dbManager = DbManager("C:/Users/farna/documents/P2-Bulk-Club-Project/BulkClub.db");
};

#endif // CONFIRMUPDATE_H
