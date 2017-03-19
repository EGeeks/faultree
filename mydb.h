#ifndef MYDB_H
#define MYDB_H

#include <QDebug>
#include <QSqlDatabase>

#define DB_NAME "tree.sqlite"

class MyDB
{
public:
    MyDB();

    static MyDB *get_instance()
    {
        static MyDB db;
        return &db;
    }

    void connect();
    bool isConnOK();

private:
    QSqlDatabase db;
    bool m_conn;        //数据库是否连接成功
};

#endif // MYDB_H
