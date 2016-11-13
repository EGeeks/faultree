#include "mydb.h"

MyDB::MyDB()
{
    m_conn = false;
}

void MyDB::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString(DB_NAME));
    if (!db.open()) {
        qDebug() << "Database Error!";
        m_conn = false;
    }
    m_conn =  true;
}

bool MyDB::isConnOK()
{
    return m_conn;
}
