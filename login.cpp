#include "login.h"
#include "ui_login.h"

#include <QDebug>

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

    if(username == "admin" && userpasswd == "admin") {
        qDebug() << "Login Success !!!";
    }
}

void Login::on_exitPushButton_clicked()
{
    this->close();
}
