#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

/**
 * @brief Constructor
 *
 * Constructor sets up connection with db and opens it
 * @param path - absolute path to db file
 */
DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

    QSqlQuery query;
    query.prepare("PRAGMA foreign_keys = ON");

    if(query.exec())
    {
        qDebug() << "foreign keys on";
    }
}

/**
 * @brief checks to see if DbManager is able to reopen
 * @return true - DbManager will reopen, false - DbManager will not reopen
 */
bool DbManager::reOpen()
{
    bool answer = false;

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("C:/Users/Nick/source/repos/P2-Bulk-Club-Project/BulkClub.db");

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
        answer = true;
    }

    return answer;
}

/**
 * @brief Destructor
 *
 * Close the db connection
 */
DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

/**
 * @brief checks to see if DbManager is open
 * @return true - DbManager is open, false - DbManager is closed
 */
bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

/**
 * @brief Creates a new 'people' table if it doesn't already exist
 * @return true - 'people' table created successfully, false - table not created
 */
bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE people(id INTEGER PRIMARY KEY, name TEXT");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'people': one might already exist.";
        success = false;
    }

    return success;
}

/**
 * @brief checks to see if the username exists
 * @param name of the user
 * @return true - username exists, false - username does not exist
 */
bool DbManager::usernameExists(const QString& username) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username FROM BulkClub WHERE (username) = (:username)");
    checkQuery.bindValue(":username", username);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
            QString username = checkQuery.value("username").toString();
            qDebug() << username;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery.lastError();
    }

    return exists;
}

/**
 * @brief checks to see if the name entered exists within the database
 * @param name of the user
 * @return true - name exists, false - name does not exist within the database
 */
bool DbManager::nameExists(const QString &name) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM customers WHERE (name) = (:name)");
    checkQuery.bindValue(":name", name);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
            QString name = checkQuery.value("name").toString();
            qDebug() << name;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::idExists(const QString &id) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM customers WHERE (id) = (:id)");
    checkQuery.bindValue(":id", id);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
            QString name = checkQuery.value("id").toString();
            qDebug() << name;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery.lastError();
    }

    return exists;
}


bool DbManager::productExists(const QString& name) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM products WHERE (name) = (:name)");
    checkQuery.bindValue(":name", name);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
            QString username = checkQuery.value("username").toString();
            qDebug() << username;
        }
    }
    else
    {
        qDebug() << "product exists failed: " << checkQuery.lastError();
    }

    return exists;
}

/**
 * @brief checks to see if the email entered exists within the database
 * @param email of the user
 * @return true - email exists, false - email does not exist within the database
 */
bool DbManager::emailExists(const QString &email) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT email FROM BulkClub WHERE (email) = (:email)");
    checkQuery.bindValue(":email", email);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
            QString email = checkQuery.value("email").toString();
            qDebug() << email;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery.lastError();
    }

    return exists;
}

/**
 * @brief checks to see if the username entered is an admin
 * @param username of the user
 * @return true - will enable admin login, false - the person is not an admin
 */
bool DbManager::CheckAdmin(const QString& username) const
{
    bool admin = false;
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT admin FROM login WHERE (username) = (:username)");
    checkQuery.bindValue(":username", username);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            admin = checkQuery.value("admin").toBool();
            qDebug() << admin;
        }
    }
    else
    {
        qDebug() << "2person exists failed: " << checkQuery.lastError();
    }
    if(admin)
    {
        qDebug() << "Admin" << endl;
    }
    return admin;
}

/**
 * @brief Gets password from user
 * @param name of the user(s)
 * @return obtains the password from user
 */
QString DbManager::GetPassword(const QString& username) const
{
    QString password;
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT password FROM login WHERE (username) = (:username)");
    checkQuery.bindValue(":username", username);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            password = checkQuery.value("password").toString();
            qDebug() << password;
        }
    }
    else
    {
        qDebug() << "person 1exists failed: " << checkQuery.lastError();
    }

    return password;
}

/**
 * @brief updates the account with new information
 * @param username, password, name, address, city of the user, value changing and admin ability to change information
 * @return true - updates account information, false - does not allow account to be updates
 */
bool DbManager::updateAccount(const QString &change, const QString &user)
{
    bool success = false;

    if(nameExists(user))
    {
        QSqlQuery query;
        query.prepare("UPDATE customers SET (type) = (:n) WHERE (name) = (:un)");
        query.bindValue(":n", change);
        query.bindValue(":un", user);

        if(query.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "update customer failed: " << query.lastError();
        }
    }
    else if(idExists(user))
    {
        QSqlQuery query;
        query.prepare("UPDATE customers SET (type) = (:n) WHERE (id) = (:un)");
        query.bindValue(":n", change);
        query.bindValue(":un", user);

        if(query.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "update customer failed: " << query.lastError();
        }
    }

    return success;
}

/**
 * @brief used for updating the customer
 * @param email of the user
 * @return true - will allow a menu to edit the customer associated with the email, false - will not allow for any updating within an account
 */
bool DbManager::insertEmailR(const QString &email)
{
    bool success = false;

    QSqlQuery query("INSERT INTO BulkClub (email) VALUES (?)");
    query.addBindValue(email);

    if(query.exec())
    {
        QSqlQuery query2;
        query2.prepare("UPDATE BulkClub SET (received) = (:re) WHERE (email) = (:em)");
        query2.bindValue(":re", 1);
        query2.bindValue(":em", email);
        if(query2.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "update customer failed: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "update customer failed: " << query.lastError();
    }

    return success;
}


/**
 * @brief ensures that the email has been received by the user
 * @param email of the user
 * @return true - email has been received, false - email was not receiver by user
 */
bool DbManager::emailRecieved(const QString &email)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("UPDATE BulkClub SET (received) = (:re) WHERE (email) = (:em)");
    query.bindValue(":re", 1);
    query.bindValue(":em", email);

    if (query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "update pamphlet recieved failed: " << query.lastError();
    }

    return success;
}

/**
 * @brief checks to see if it is possible to make an account
 * @param username, password, name, address, city, and email of the user
 * @return true - adds the account, false - does not add the account
 */
bool DbManager::addAccount(const QString &id, const QString &name, const QString &expire, const QString &type)
{
    bool success = false;
    if (!name.isEmpty())
    {
        QSqlQuery query("INSERT INTO customers (id, name, expire, type) VALUES (?,?,?,?)");
        query.addBindValue(id);
        query.addBindValue(name);
        query.addBindValue(expire);
        query.addBindValue(type);

        if(query.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "add person failed: name cannot be empty";
    }

    return success;
}

bool DbManager::removeCustomerId(const QString &ID)
{
    bool success = false;

    if (idExists(ID))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM customers WHERE (id) = (:id)");
        queryDelete.bindValue(":id", ID);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove person failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove person failed: person doesnt exist";
        qDebug() << ID;
    }

    return success;
}

/**
 * @brief removes customer from email list
 * @param email of the user
 * @return true - will remove the user's email from the database, false - will keep the user's email within the database
 */
bool DbManager::removeCustomer(const QString &username)
{
    bool success = false;

    if (nameExists(username))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM customers WHERE (name) = (:name)");
        queryDelete.bindValue(":name", username);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove person failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove person failed: person doesnt exist";
        qDebug() << username;
    }

    return success;
}

/**
 * @brief removes customer from email list
 * @param email of the user
 * @return true - will remove the user's email from the database, false - will keep the user's email within the database
 */
bool DbManager::removeEmailCustomer(const QString &email)
{
    bool success = false;

    if(emailExists(email))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM BulkClub WHERE (email) = (:em)");
        queryDelete.bindValue(":em", email);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove person failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove person failed: person doesnt exist";
        qDebug() << email;
    }

    return success;
}

/**
 * @brief checks to see if it is possible to make a purchase
 * @param username, item1Count, item2Count, item3Count, and total cost of products in cart
 * @return true - makes the purchase, false - does not make purchase
 */
bool DbManager::makePurchase(const int &id, const QString &name, const QString &product, const int &quantity, const double &price, const QString &type, const QDate &date)
{

    bool success = false;


    QTime time = QTime::currentTime();

    QSqlQuery query;
    query.prepare("INSERT INTO purchases (id, name, type, product, quantity, price, date, time) VALUES ( :id , :name , :type, :product , :quantity , :price , :date , :time )");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":type", type);
    query.bindValue(":product", product);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":time", time);

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "add purchase failed: " << query.lastError();
    }


    return success;
}


/**
 * @brief submits the testimonials for the customers who have already bought products
 * @param text from user, and their username
 * @return true - adds the testimonial, false - does not add the testimonial
 */
bool DbManager::submitTestimonials(const QString &text, const QString &username)
{

    bool success = false;
    QString name;

    QSqlQuery query;
    query.prepare("SELECT name FROM BulkClub WHERE (username) = (:username)");
    query.bindValue(":username", username);

    if (query.exec())
    {
        if (query.next())
        {
            name = query.value("name").toString();
            qDebug() << name;
        }
    }

    QDate date = QDate::currentDate();
    query.prepare("INSERT INTO testimonials (testimonial, username, name, date) VALUES (?,?,?,?)");
    query.addBindValue(text);
    query.addBindValue(username);
    query.addBindValue(name);
    query.addBindValue(date);

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "add testimonials: " << query.lastError();
    }


    return success;



}

/**
 * @brief checks to see see if the user can update their testimonial
 * @param text of the user, whether the testimonial is approved, and whether it is approved or not, and their id
 * @return true - updates the testimonial, false - keeps the testimonial as is
 */
bool DbManager::updateTestimonial(const QString &text, const bool approved, const int id)
{
    bool success = false;
    QString name;

    QSqlQuery query;
    query.prepare("UPDATE testimonials SET (testimonial, approved) = ( :testimonials , :approved ) WHERE (id) = (:id)");
    query.bindValue(":testimonials", text);
    query.bindValue(":approved", approved);
    query.bindValue(":id", id);

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "update testimonials: " << query.lastError();
    }


    return success;
}

/**
 * @brief checks to see if the user can remove their testimonial from the website
 * @param id of the user
 * @return true - removes the testimonial, false - keeps the testimonial
 */
bool DbManager::removeTestimonial(const int id)
{
    bool success = false;

    QSqlQuery queryDelete;
    queryDelete.prepare("DELETE FROM testimonials WHERE id = (:id)");
    queryDelete.bindValue(":id", id);
    success = queryDelete.exec();

    if(!success)
    {
        qDebug() << "remove testimonial failed: " << queryDelete.lastError();
    }


return success;
}



bool DbManager::generateSalesReport(const QDate &startDate, const QDate &endDate, QSqlQueryModel *model, double &total)
{

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT SUM(total) FROM purchases WHERE date >= (:start) AND date <= (:end)");
    qry->bindValue(":start", startDate);
    qry->bindValue(":end", endDate);



    if(qry->exec())
    {
        qry->next();
        total = qry->value(0).toDouble();
    }
    else
    {
        qDebug() << "fail!";
    }


    qry->prepare("SELECT * FROM purchases WHERE date >= (:start) AND date <= (:end) ORDER by time ASC");
    qry->bindValue(":start", startDate);
    qry->bindValue(":end", endDate);


    if(qry->exec())
    {
        model->setQuery(*qry);

        return true;
    }
    else
    {
        qDebug() << "fail!";

        return false;
    }
}

bool DbManager::updateCustomerRevenue(const int &id, const double &revenue)
{
    bool success = false;
    QString name;

    QSqlQuery query;
    query.prepare("UPDATE customers SET (total, rebate) = ( ( :total + total ) , ( rebate + :rebate ) ) WHERE (id) = (:id)");
    query.bindValue(":total", revenue);
    query.bindValue(":rebate", (QString::number( (revenue*.02), 'f', 2).toDouble()));
    query.bindValue(":id", id);

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "update customer totals: " << query.lastError();
    }


    return success;

}


bool DbManager::updateProductFromPurchase(const QString &name, const double &quantity, const double &revenue)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("UPDATE products SET (sold, revenue) = ( ( :quantity + sold ) , ( revenue + :revenue ) ) WHERE (name) = (:name)");
    query.bindValue(":quantity", quantity);
    query.bindValue(":revenue", revenue);
    query.bindValue(":name", name);

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "update product totals: " << query.lastError();
    }


    return success;

}
