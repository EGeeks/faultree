#include "treemanageform.h"
#include "ui_treemanageform.h"
#include "addtreenodedialog.h"

TreeManageForm::TreeManageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeManageForm)
{
    ui->setupUi(this);

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

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
void TreeManageForm::addSecondNode(QTreeWidgetItem *parentItem)
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
void TreeManageForm::addThirdNode(QTreeWidgetItem *parentItem)
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

//添加父节点
void TreeManageForm::addParnetNodeDialog()
{
    AddTreeNodeDialog *dialog = new AddTreeNodeDialog();
    dialog->setParentNodeID(0);
    dialog->exec();

    qDebug() << "nodeID : " << dialog->getNodeID();
    QSqlQuery query;
    QString sql = QString("SELECT * FROM tree WHERE nodeID == %1").arg(dialog->getNodeID());
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

        ui->treeWidget->addTopLevelItem(item);
    }
}

//添加子节点
void TreeManageForm::addChildNodeDialog()
{
    AddTreeNodeDialog *dialog = new AddTreeNodeDialog();
    dialog->setParentNodeID(ui->treeWidget->currentItem()->data(0, DB_TREE_NODEID).toInt());
    dialog->exec();

    qDebug() << "nodeID : " << dialog->getNodeID();
    QSqlQuery query;
    QString sql = QString("SELECT * FROM tree WHERE nodeID == %1").arg(dialog->getNodeID());
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

        ui->treeWidget->currentItem()->addChild(item);
    }
}

// 删除节点
void TreeManageForm::delNode()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    if(item->parent() == NULL) {
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->currentIndex().row());
    } else {
        item->parent()->takeChild(ui->treeWidget->currentIndex().row());
    }

    // 从数据库中删除
    int nodeID = item->data(0, DB_TREE_NODEID).toInt();

    QSqlQuery query;
    QString sql = QString("DELETE FROM tree WHERE nodeID=%1")
            .arg(nodeID);
    query.exec(sql);
}

// 点击listview 触发
void TreeManageForm::on_treeWidget_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);

    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    int nodeID = item->data(0, DB_TREE_NODEID).toInt();
    int ErrID = item->data(0, DB_TREE_ERR_ID).toInt();
    QString ErrDesc = item->data(0, DB_TREE_ERR_DESC).toString();
    int ruleID = item->data(0, DB_TREE_RULE_ID).toInt();

    ui->lineEdit_ErrDesc->setText(ErrDesc);
    ui->lineEdit_nodeID->setText(QString::number(nodeID));
    ui->lineEdit_errID->setText(QString::number(ErrID));
    ui->textEdit_ruleID->clear();

    int alias = 0;
    QSqlQuery query;
    QString sql = QString("SELECT * FROM rule WHERE ruleID == %1;").arg(ruleID);
    query.exec(sql);
    if(!query.next()) {
        // ui->lineEdit_ruleID->setText("ruleID " + ruleID);
        return;
    }
    alias = query.value("alias").toInt();

    sql = QString("SELECT * FROM rule WHERE alias == %1;").arg(alias);
    query.exec(sql);
    while (query.next()) {
        int rule_id = query.value("ruleID").toInt();
        ui->textEdit_ruleID->append(QString::number(rule_id));
    }
}

void TreeManageForm::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget->itemAt(pos);

    QMenu *popMenu = new QMenu(this);
    QAction *addRoot = new QAction("添加根节点", this);
    connect(addRoot, SIGNAL(triggered()), this, SLOT(addParnetNodeDialog()));
    popMenu->addAction(addRoot);

    if(item != NULL) {
        QAction *addNextNode = new QAction("添加子节点", this);
        connect(addNextNode, SIGNAL(triggered()), this, SLOT(addChildNodeDialog()));
        popMenu->addAction(addNextNode);

        if(item->childCount() == 0) {
            // 不在有子节点
            QAction *delNode = new QAction("删除节点", this);
            connect(delNode, SIGNAL(triggered()), this, SLOT(delNode()));
            popMenu->addAction(delNode);
        }
    }

    popMenu->exec(QCursor::pos());
    popMenu->deleteLater();
}
