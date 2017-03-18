#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLabel>
#include <QMainWindow>
#include "login.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
      void on_LoginPass(QString username);

protected:

    void timerEvent(QTimerEvent *e);

private:
    Ui::MainWindow *ui;
    Login *login;
    QString m_currUsername;

    QLabel *label1;
    QLabel *label2;
    int m_statusbarTimeID;

};

#endif // MAINWINDOW_H
