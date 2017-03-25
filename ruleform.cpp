#include "ruleform.h"
#include "ui_ruleform.h"

RuleForm::RuleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RuleForm)
{
    ui->setupUi(this);

    listAllNode();
}

RuleForm::~RuleForm()
{
    delete ui;
}

// 创建root 节点
void RuleForm::listAllNode()
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
void RuleForm::addSecondNode(QTreeWidgetItem *parentItem)
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
void RuleForm::addThirdNode(QTreeWidgetItem *parentItem)
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

void RuleForm::updateRule(QTreeWidgetItem *item)
{
    int row = 0;
    int ruleID = item->data(0, DB_TREE_RULE_ID).toInt();

    QSqlQuery query;
    QString sql = QString("SELECT * FROM rule WHERE ruleID == %1")
            .arg(ruleID);

    query.exec(sql);
    while (query.next()) {
        int nodeID = query.value("ruleID").toInt();
        QString errDesc = query.value("errDesc").toString();
        QString detectTip = query.value("detectTip").toString();
        int depandErrID = query.value("depandErrID").toInt();
        int paramID = query.value("paramID").toInt();
        int Judg = query.value("Judg").toInt();
        QString errReason = query.value("errReason").toString();
        QString Suggest = query.value("Suggest").toString();

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(nodeID)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(errDesc));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(detectTip));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(depandErrID)));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(paramID)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(Judg)));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(errReason));
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(Suggest));

        row++;
    }
}

void RuleForm::on_treeWidget_clicked(const QModelIndex &index)
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    updateRule(item);
}