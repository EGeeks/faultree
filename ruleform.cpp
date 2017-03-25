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
void RuleForm::addSecondNode(QStandardItem *parentItem)
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
void RuleForm::addThirdNode(QStandardItem *parentItem)
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

void RuleForm::updateRule(QStandardItem *item)
{
    int row = 0;
    int ruleID = item->data(DB_TREE_RULE_ID).toInt();

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

void RuleForm::on_treeView_clicked(const QModelIndex &index)
{
    QStandardItemModel *model = (QStandardItemModel *)ui->treeView->model();
    QStandardItem *item = model->itemFromIndex(index);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    updateRule(item);
}
