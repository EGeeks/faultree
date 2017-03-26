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

// 根据关键字搜索
void ZhenDuanForm::searchByKeyword(QString keyword)
{
    for(int n = 0; n < ui->treeWidget->topLevelItemCount(); n++) {
        QTreeWidgetItem *topItem = ui->treeWidget->topLevelItem(n);

        for(int m = 0; m < topItem->childCount(); m++) {
            QTreeWidgetItem *itemChildOne = topItem->child(m);
            QString ErrDescOne = itemChildOne->data(0, DB_TREE_ERR_DESC).toString();
            if(ErrDescOne.indexOf(keyword, Qt::CaseInsensitive) != -1)
                ui->treeWidget->expandItem(topItem);

            for(int s = 0; s < itemChildOne->childCount(); s++) {
                QTreeWidgetItem *itemChildTwo = itemChildOne->child(s);
                QString ErrDescTwo = itemChildTwo->data(0, DB_TREE_ERR_DESC).toString();
                if(ErrDescTwo.indexOf(keyword, Qt::CaseInsensitive) != -1) {
                    ui->treeWidget->expandItem(itemChildOne);
                    ui->treeWidget->expandItem(topItem);
                }
            }
        }
    }
}

// 根据alarmID 搜索
void ZhenDuanForm::searchByAlarmID(QString alarmID)
{
    for(int n = 0; n < ui->treeWidget->topLevelItemCount(); n++) {
        QTreeWidgetItem *topItem = ui->treeWidget->topLevelItem(n);

        for(int m = 0; m < topItem->childCount(); m++) {
            QTreeWidgetItem *itemChildOne = topItem->child(m);
            QString alarmIDone = itemChildOne->data(0, DB_TREE_ALARM_ID).toString();
            if(alarmIDone.indexOf(alarmID) != -1)
                ui->treeWidget->expandItem(topItem);

            for(int s = 0; s < itemChildOne->childCount(); s++) {
                QTreeWidgetItem *itemChildTwo = itemChildOne->child(s);
                QString alarmIDtwo = itemChildTwo->data(0, DB_TREE_ALARM_ID).toString();
                if(alarmIDtwo.indexOf(alarmID) != -1) {
                    ui->treeWidget->expandItem(itemChildOne);
                    ui->treeWidget->expandItem(topItem);
                }
            }
        }
    }
}

void ZhenDuanForm::on_radioButton_keyWord_toggled(bool checked)
{
    Q_UNUSED(checked);

    // 清空搜索框
    ui->lineEdit_search->clear();
}

void ZhenDuanForm::on_radioButton_alarmID_toggled(bool checked)
{
    Q_UNUSED(checked);

    // 清空搜索框
    ui->lineEdit_search->clear();
}

// 关键字变化触发搜索
void ZhenDuanForm::on_lineEdit_search_textChanged(const QString &arg1)
{
    if(ui->lineEdit_search->text().isEmpty())
        return;

    ui->treeWidget->collapseAll();

    if(ui->radioButton_keyWord->isChecked() == true) {
        searchByKeyword(arg1);
    } else if(ui->radioButton_alarmID->isChecked() == true) {
        searchByAlarmID(arg1);
    }
}

