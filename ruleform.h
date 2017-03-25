#ifndef RULEFORM_H
#define RULEFORM_H

#include <QDebug>
#include <QSqlQuery>
#include <QWidget>
#include <QStandardItemModel>

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
    void addSecondNode(QStandardItem *parentItem);
    void addThirdNode(QStandardItem *parentItem);

    void updateRule(QStandardItem *item);

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::RuleForm *ui;
};

#endif // RULEFORM_H
