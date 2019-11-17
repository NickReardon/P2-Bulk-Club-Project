#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QSqlDatabase>
#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlQueryModel>

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 people.db
 * 2. sqilte> CREATE TABLE people(ids integer primary key, name text);
 * 3. sqlite> .quit
 */
class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    /**
     * @brief checks to see if DbManager is open
     * @return true - DbManager is open, false - DbManager is closed
     */
    bool isOpen() const;

    /**
     * @brief checks to see if DbManager is able to reopen
     * @return true - DbManager will reopen, false - DbManager will not reopen
     */
    bool reOpen();

    /**
     * @brief Creates a new 'people' table if it doesn't already exist
     * @return true - 'people' table created successfully, false - table not created
     */
    bool createTable();

    /**
     * @brief Gets password from user
     * @param name of the user(s)
     * @return obtains the password from user
     */
    QString GetPassword(const QString &username) const;

    /**
     * @brief updates the account with new information
     * @param username, password, name, address, city of the user, value changing and admin ability to change information
     * @return true - updates account information, false - does not allow account to be updates
     */
    bool updateAccount(const QString &username, const QString &password, const QString &name, const QString &address, const QString &city, const QString &email, const QString &value, const int admin, const QString& interest);

    /**
     * @brief checks to see if the username entered is an admin
     * @param username of the user
     * @return true - will enable admin login, false - the person is not an admin
     */
    bool CheckAdmin(const QString &username) const;

    /**
     * @brief checks to see if the username exists
     * @param name of the user
     * @return true - username exists, false - username does not exist
     */
    bool usernameExists(const QString &name) const;

    /**
     * @brief checks to see if the name entered exists within the database
     * @param name of the user
     * @return true - name exists, false - name does not exist within the database
     */
    bool nameExists(const QString &name) const;

    /**
     * @brief checks to see if the email entered exists within the database
     * @param email of the user
     * @return true - email exists, false - email does not exist within the database
     */
    bool emailExists(const QString &email) const;

    /**
     * @brief checks to see if it is possible to make an account
     * @param username, password, name, address, city, and email of the user
     * @return true - adds the account, false - does not add the account
     */
    bool addAccount(const QString &id, const QString &name, const QString &expire, const QString &type);

    /**
     * @brief ensures that the email has been received by the user
     * @param email of the user
     * @return true - email has been received, false - email was not receiver by user
     */
    bool emailRecieved(const QString &email);

    /**
     * @brief removes customer
     * @param username of the user
     * @return true - will remove user from database, false - will keep the user within the database
     */
    bool removeCustomer(const QString &username);

    /**
     * @brief removes customer from email list
     * @param email of the user
     * @return true - will remove the user's email from the database, false - will keep the user's email within the database
     */
    bool removeEmailCustomer(const QString &email);

    /**
     * @brief used for updating the customer
     * @param email of the user
     * @return true - will allow a menu to edit the customer associated with the email, false - will not allow for any updating within an account
     */
    bool insertEmailR(const QString &email);

    /**
     * @brief checks to see if it is possible to make a purchase
     * @param username, item1Count, item2Count, item3Count, and total cost of products in cart
     * @return true - makes the purchase, false - does not make purchase
     */
    bool makePurchase(const QString &username, const int item1Count, const int item2Count, const int item3Count, const double total);

    /**
     * @brief submits the testimonials for the customers who have already bought products
     * @param text from user, and their username
     * @return true - adds the testimonial, false - does not add the testimonial
     */
    bool submitTestimonials( const QString &text, const QString &username);

    /**
     * @brief checks to see see if the user can update their testimonial
     * @param text of the user, whether the testimonial is approved, and whether it is approved or not, and their id
     * @return true - updates the testimonial, false - keeps the testimonial as is
     */
    bool updateTestimonial(const QString &text, const bool approved, const int id);

    /**
     * @brief checks to see if the user can remove their testimonial from the website
     * @param id of the user
     * @return true - removes the testimonial, false - keeps the testimonial
     */
    bool removeTestimonial(const int id);
private:
    QSqlDatabase m_db;
};


#endif // DBMANAGER_H
