#ifndef ZHENDUANFORM_H
#define ZHENDUANFORM_H

#include <QDebug>
#include <QSqlQuery>
#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class ZhenDuanForm;
}

//对应tree 表中的属性
enum DBTreeKey {
    DB_TREE_NODEID = Qt::UserRole + 100,
    DB_TREE_PARENT_NODEID,
    DB_TREE_ERR_ID,
    DB_TREE_ERR_DESC,
    DB_TREE_RULE_ID,
    DB_TREE_ALARM_ID,
};

class ZhenDuanForm : public QWidget
{
    Q_OBJECT

public:
    explicit ZhenDuanForm(QWidget *parent = 0);
    ~ZhenDuanForm();

protected:
    void listAllNode();
    void addSecondNode(QStandardItem *parentItem);
    void addThirdNode(QStandardItem *parentItem);

private:
    Ui::ZhenDuanForm *ui;
};

#endif // ZHENDUANFORM_H
