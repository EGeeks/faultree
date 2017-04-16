#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class AccountDialog;
}

class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = 0);
    ~AccountDialog();

protected:
    void ListDB();

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_modify_clicked();

private:
    Ui::AccountDialog *ui;
};

#endif // ACCOUNTDIALOG_H
