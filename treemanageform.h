#ifndef TREEMANAGEFORM_H
#define TREEMANAGEFORM_H

#include <QDebug>
#include <QSqlQuery>
#include <QWidget>
#include <QStandardItemModel>

#include "common.h"

namespace Ui {
class TreeManageForm;
}

class TreeManageForm : public QWidget
{
    Q_OBJECT

public:
    explicit TreeManageForm(QWidget *parent = 0);
    ~TreeManageForm();

protected:
    void listAllNode();
    void addSecondNode(QStandardItem *parentItem);
    void addThirdNode(QStandardItem *parentItem);

private:
    Ui::TreeManageForm *ui;
};

#endif // TREEMANAGEFORM_H
