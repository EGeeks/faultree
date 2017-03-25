#include "zhenduanform.h"
#include "ui_zhenduanform.h"


ZhenDuanForm::ZhenDuanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZhenDuanForm)
{
    ui->setupUi(this);

    listAllNode();
}

ZhenDuanForm::~ZhenDuanForm()
{
    delete ui;
}

// 创建root 节点
void ZhenDuanForm::listAllNode()
{
    QSqlQuery query;

    query.exec("SELECT * FROM tree WHERE parentNodeID == 0");
    while (query.next()) {
        int nodeID = query.value("nodeID").toInt();
        int parentNodeID = query.value("parentNodeID").toInt();
        int ErrID = query.value("ErrID").toInt();
        QString ErrDesc = query.value("ErrDesc").toString();
        QString ruleID = query.value("ruleID").toString();
        QString alarmID = query.value("alarmID").toString();

        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << ErrDesc);
        item->setData(0, DB_TREE_NODEID, nodeID);
        item->setData(0, DB_TREE_PARENT_NODEID, parentNodeID);
        item->setData(0, DB_TREE_ERR_ID, ErrID);
        item->setData(0, DB_TREE_ERR_DESC, ErrDesc);
        item->setData(0, DB_TREE_RULE_ID, ruleID);
        item->setData(0, DB_TREE_ALARM_ID, alarmID);

        ui->treeWidget->addTopLevelItem(item);
        addSecondNode(item);
    }
}

// 创建第二层 节点
void ZhenDuanForm::addSecondNode(QTreeWidgetItem *parentItem)
{
    int parent_node = parentItem->data(0, DB_TREE_NODEID).toInt();

    QSqlQuery query;
    QString sql = QString("SELECT * FROM tree WHERE parentNodeID == %1")
            .arg(parent_node);

    query.exec(sql);
    while (query.next()) {
        int nodeID = query.value("nodeID").toInt();
        int parentNodeID = query.value("parentNodeID").toInt();
        int ErrID = query.value("ErrID").toInt();
        QString ErrDesc = query.value("ErrDesc").toString();
        QString ruleID = query.value("ruleID").toString();
        QString alarmID = query.value("alarmID").toString();

        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << ErrDesc);
        item->setData(0, DB_TREE_NODEID, nodeID);
        item->setData(0, DB_TREE_PARENT_NODEID, parentNodeID);
        item->setData(0, DB_TREE_ERR_ID, ErrID);
        item->setData(0, DB_TREE_ERR_DESC, ErrDesc);
        item->setData(0, DB_TREE_RULE_ID, ruleID);
        item->setData(0, DB_TREE_ALARM_ID, alarmID);


        parentItem->addChild(item);
        addThirdNode(item);
    }
}

// 创建第三层节点
void ZhenDuanForm::addThirdNode(QTreeWidgetItem *parentItem)
{
    int parent_node = parentItem->data(0, DB_TREE_NODEID).toInt();

    QSqlQuery query;
    QString sql = QString("SELECT * FROM tree WHERE parentNodeID == %1")
            .arg(parent_node);

    query.exec(sql);
    while (query.next()) {
        int nodeID = query.value("nodeID").toInt();
        int parentNodeID = query.value("parentNodeID").toInt();
        int ErrID = query.value("ErrID").toInt();
        QString ErrDesc = query.value("ErrDesc").toString();
        QString ruleID = query.value("ruleID").toString();
        QString alarmID = query.value("alarmID").toString();

        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << ErrDesc);
        item->setData(0, DB_TREE_NODEID, nodeID);
        item->setData(0, DB_TREE_PARENT_NODEID, parentNodeID);
        item->setData(0, DB_TREE_ERR_ID, ErrID);
        item->setData(0, DB_TREE_ERR_DESC, ErrDesc);
        item->setData(0, DB_TREE_RULE_ID, ruleID);
        item->setData(0, DB_TREE_ALARM_ID, alarmID);

        parentItem->addChild(item);
        addThirdNode(item);
    }
}


