#ifndef TREEMANAGEFORM_H
#define TREEMANAGEFORM_H

#include <QDebug>
#include <QMenu>
#include <QSqlQuery>
#include <QWidget>
#include <QTreeWidgetItem>

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
    void addSecondNode(QTreeWidgetItem *parentItem);
    void addThirdNode(QTreeWidgetItem *parentItem);

protected slots:
    void addParnetNodeDialog();
    void addChildNodeDialog();
    void delNode();

private slots:
    void on_treeWidget_clicked(const QModelIndex &index);
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::TreeManageForm *ui;
};

#endif // TREEMANAGEFORM_H
