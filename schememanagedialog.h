#ifndef SCHEMEMANAGEDIALOG_H
#define SCHEMEMANAGEDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>


namespace Ui {
class SchemeManageDialog;
}

class SchemeManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SchemeManageDialog(QWidget *parent = 0);
    ~SchemeManageDialog();

protected:
    void listDB();

private slots:
    void on_addPushButton_clicked();
    void on_editPushButton_clicked();
    void on_delPushButton_clicked();
    void on_exitPushButton_clicked();

private:
    Ui::SchemeManageDialog *ui;
};

#endif // SCHEMEMANAGEDIALOG_H
