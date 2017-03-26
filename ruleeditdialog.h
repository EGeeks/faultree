#ifndef RULEEDITDIALOG_H
#define RULEEDITDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class RuleEditDialog;
}

class RuleEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RuleEditDialog(QWidget *parent = 0);
    ~RuleEditDialog();

    void setMode(bool mode);
    void setRuleEditData(int ruleID, QString errDesc, QString detectTip, QString paramID, int Judg,
                         QString schemeID);

private slots:
    void on_pushButton_clicked();

private:
    Ui::RuleEditDialog *ui;

    bool m_mode;  // true : 添加 false: 编辑
};

#endif // RULEEDITDIALOG_H
