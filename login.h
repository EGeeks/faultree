#ifndef LOGIN_H
#define LOGIN_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_loginPushButton_clicked();
    void on_exitPushButton_clicked();

signals:
    void checkPass(QString username);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
