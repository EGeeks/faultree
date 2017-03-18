#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menubar->hide();

    login = new Login();
    connect(login, SIGNAL(checkPass()), this, SLOT(show()));
    login->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
