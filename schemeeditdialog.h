#ifndef SCHEMEEDITDIALOG_H
#define SCHEMEEDITDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class SchemeEditDialog;
}

class SchemeEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SchemeEditDialog(QWidget *parent = 0);
    ~SchemeEditDialog();

    void setMode(bool mode);
    void setRuleEditData(QString schemeID, QString schemeDesc, QString repair);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SchemeEditDialog *ui;

    bool m_mode;  // true : 添加 false: 编辑
};

#endif // SCHEMEEDITDIALOG_H
