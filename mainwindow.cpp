#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置状态栏
    label1 = new QLabel(this);
    label1->setText("[欢迎使用数控机床人机交互系统]");
    label2 = new QLabel(this);
    label2->setText("当前用户");
    ui->statusbar->addWidget(label1);
    ui->statusbar->addWidget(label2);

    m_statusbarTimeID = startTimer(1000);

    ui->menubar->hide();

    login = new Login();
    connect(login, SIGNAL(checkPass(QString)), this, SLOT(on_LoginPass(QString)));
    login->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::on_LoginPass(QString username)
 {
     m_currUsername = username;
     login->close();
     this->show();
 }


void MainWindow::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_statusbarTimeID) {
        // 定时更新状态栏时间
        QString time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
        label2->setText("当前用户:" + m_currUsername + " 当前时间: " + time);
    }
}
