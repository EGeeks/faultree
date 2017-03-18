#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLabel>
#include <QMainWindow>
#include "login.h"
#include "centerform.h"

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

private slots:
    void on_zhenduanAction_triggered();

    void on_treeMangeAction_triggered();

    void on_ruleAction_triggered();

    void on_fileAction_triggered();

    void on_maintrainAction_triggered();

    void on_helpToolAction_triggered();

private:
    Ui::MainWindow *ui;
    Login *login;
    QString m_currUsername;

    QLabel *label1;
    QLabel *label2;
    int m_statusbarTimeID;

    CenterForm *centerForm;

};

#endif // MAINWINDOW_H
