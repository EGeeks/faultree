#ifndef RULEMANAGEDIALOG_H
#define RULEMANAGEDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class RuleManageDialog;
}

class RuleManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RuleManageDialog(QWidget *parent = 0);
    ~RuleManageDialog();

protected:
    void listDB();

private slots:
    void on_addPushButton_clicked();
    void on_delPushButton_clicked();
    void on_editPushButton_clicked();
    void on_exitPushButton_clicked();

private:
    Ui::RuleManageDialog *ui;
};

#endif // RULEMANAGEDIALOG_H
