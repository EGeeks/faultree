#ifndef PARAMMANAGEDIALOG_H
#define PARAMMANAGEDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class ParamManageDialog;
}

class ParamManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParamManageDialog(QWidget *parent = 0);
    ~ParamManageDialog();

    void listDB();

private slots:
    void on_addPushButton_clicked();
    void on_delPushButton_clicked();
    void on_editPushButton_clicked();
    void on_exitPushButton_clicked();

private:
    Ui::ParamManageDialog *ui;
};

#endif // PARAMMANAGEDIALOG_H
