#ifndef RULEFORM_H
#define RULEFORM_H

#include <QDebug>
#include <QSqlQuery>
#include <QWidget>
#include <QTreeWidgetItem>

#include "common.h"

namespace Ui {
class RuleForm;
}

class RuleForm : public QWidget
{
    Q_OBJECT

public:
    explicit RuleForm(QWidget *parent = 0);
    ~RuleForm();

protected:
    void listAllNode();
    void addSecondNode(QTreeWidgetItem *parentItem);
    void addThirdNode(QTreeWidgetItem *parentItem);

    void updateRule(QTreeWidgetItem *item);

private slots:
    void on_treeWidget_clicked(const QModelIndex &index);
    void on_pushButton_ruleManage_clicked();
    void on_pushButton_paramManage_clicked();

private:
    Ui::RuleForm *ui;
};

#endif // RULEFORM_H
