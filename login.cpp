#include "login.h"
#include "ui_login.h"

#include <QDebug>
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);


}

Login::~Login()
{
    delete ui;
}


void Login::on_loginPushButton_clicked()
{
    QString username   = ui->usernameLineEdit->text();
    QString userpasswd = ui->userpasswdLineEdit->text();

    if(username.isEmpty())
        QMessageBox::information(NULL, "提示", "请输入用户名");

    if(userpasswd.isEmpty())
        QMessageBox::information(NULL, "提示", "请输入用户名");


    QSqlQuery query;
    QString sql = QString("SELECT COUNT(1) as count FROM user WHERE username='%1' AND password='%2';")
            .arg(username)
            .arg(userpasswd);
    query.exec(sql);
    qDebug() << "Login : " << sql;
    if(query.next() == false) {
        QMessageBox::warning(this, "错误", "数据库查询user 出错");
        return;
    }

    int count = query.value("count").toInt();
    if(count > 0) {
        emit checkPass(username);
        return;
    } else {
        QMessageBox::warning(NULL, "错误", "用户名或密码错误");
    }
}

void Login::on_exitPushButton_clicked()
{
    this->close();
}
