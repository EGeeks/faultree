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

    if(username == "admin" && userpasswd == "admin") {
        qDebug() << "Login Success !!!";
        emit checkPass(username);
    } else {
        QMessageBox::warning(NULL, "错误", "用户名或密码错误");
    }
}

void Login::on_exitPushButton_clicked()
{
    this->close();
}
