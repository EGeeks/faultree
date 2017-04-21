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
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_modify_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::AccountDialog *ui;
    bool modify_flag;
};

#endif // ACCOUNTDIALOG_H
