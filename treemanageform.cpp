#include "treemanageform.h"
#include "ui_treemanageform.h"

TreeManageForm::TreeManageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeManageForm)
{
    ui->setupUi(this);

     listAllNode();
}

TreeManageForm::~TreeManageForm()
{
    delete ui;
}

// 创建root 节点
void TreeManageForm::listAllNode()
{
    QSqlQuery query;
    int count = 0;

    query.exec("SELECT COUNT(*) FROM tree");
    while (query.next()) {
        count = query.value(0).toInt();
    }

    QStandardItemModel *model = new QStandardItemModel(count,1);
    model->setHeaderData(0, Qt::Horizontal, tr("描述"));

    int index = 0;
    query.exec("SELECT * FROM tree WHERE parentNodeID == 0");
    while (query.next()) {
        int nodeID = query.value("nodeID").toInt();
        int parentNodeID = query.value("parentNodeID").toInt();
        int ErrID = query.value("ErrID").toInt();
        QString ErrDesc = query.value("ErrDesc").toString();
        int ruleID = query.value("ruleID").toInt();
        int alarmID = query.value("alarmID").toInt();

        QStandardItem *item = new QStandardItem(ErrDesc);
        item->setData(nodeID,  DB_TREE_NODEID);
        item->setData(parentNodeID, DB_TREE_PARENT_NODEID);
        item->setData(ErrID, DB_TREE_ERR_ID);
        item->setData(ErrDesc, DB_TREE_ERR_DESC);
        item->setData(ruleID, DB_TREE_RULE_ID);
        item->setData(alarmID, DB_TREE_ALARM_ID);

        model->setItem(index, 0, item);
        addSecondNode(model->item(index));

        index++;
    }

    ui->treeView->setModel(model);
}

// 创建第二层 节点
void TreeManageForm::addSecondNode(QStandardItem *parentItem)
{
    int parent_node = parentItem->data(Qt::UserRole + 100).toInt();

    QSqlQuery query;
    QString sql = QString("SELECT * FROM tree WHERE parentNodeID == %1")
            .arg(parent_node);

    query.exec(sql);
    while (query.next()) {
        int nodeID = query.value("nodeID").toInt();
        int parentNodeID = query.value("parentNodeID").toInt();
        int ErrID = query.value("ErrID").toInt();
        QString ErrDesc = query.value("ErrDesc").toString();
        int ruleID = query.value("ruleID").toInt();
        int alarmID = query.value("alarmID").toInt();

        QStandardItem *item = new QStandardItem(ErrDesc);
        item->setData(nodeID,  DB_TREE_NODEID);
        item->setData(parentNodeID, DB_TREE_PARENT_NODEID);
        item->setData(ErrID, DB_TREE_ERR_ID);
        item->setData(ErrDesc, DB_TREE_ERR_DESC);
        item->setData(ruleID, DB_TREE_RULE_ID);
        item->setData(alarmID, DB_TREE_ALARM_ID);

        parentItem->appendRow(item);
        addThirdNode(item);
    }
}

// 创建第三层节点
void TreeManageForm::addThirdNode(QStandardItem *parentItem)
{
    int parent_node = parentItem->data(Qt::UserRole + 100).toInt();

    QSqlQuery query;
    QString sql = QString("SELECT * FROM tree WHERE parentNodeID == %1")
            .arg(parent_node);

    query.exec(sql);
    while (query.next()) {
        int nodeID = query.value("nodeID").toInt();
        int parentNodeID = query.value("parentNodeID").toInt();
        int ErrID = query.value("ErrID").toInt();
        QString ErrDesc = query.value("ErrDesc").toString();
        int ruleID = query.value("ruleID").toInt();
        int alarmID = query.value("alarmID").toInt();

        QStandardItem *item = new QStandardItem(ErrDesc);
        item->setData(nodeID,  DB_TREE_NODEID);
        item->setData(parentNodeID, DB_TREE_PARENT_NODEID);
        item->setData(ErrID, DB_TREE_ERR_ID);
        item->setData(ErrDesc, DB_TREE_ERR_DESC);
        item->setData(ruleID, DB_TREE_RULE_ID);
        item->setData(alarmID, DB_TREE_ALARM_ID);

        parentItem->appendRow(item);
        addThirdNode(item);
    }
}
