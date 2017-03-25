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

//打开添加节点对话框
void TreeManageForm::openAddDialog()
{
    AddTreeNodeDialog *dialog = new AddTreeNodeDialog();
    dialog->show();
}

// 点击listview 触发
void TreeManageForm::on_treeWidget_clicked(const QModelIndex &index)
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    int nodeID = item->data(0, DB_TREE_NODEID).toInt();
    int ErrID = item->data(0, DB_TREE_ERR_ID).toInt();
    QString ErrDesc = item->data(0, DB_TREE_ERR_DESC).toString();
    QString ruleID = item->data(0, DB_TREE_RULE_ID).toString();

    ui->lineEdit_ErrDesc->setText(ErrDesc);
    ui->lineEdit_nodeID->setText(QString::number(nodeID));
    ui->lineEdit_errID->setText(QString::number(ErrID));
    ui->lineEdit_ruleID->setText(ruleID);
}

void TreeManageForm::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget->itemAt(pos);

    QMenu *popMenu = new QMenu(this);
    QAction *addRoot = new QAction("添加根节点", this);
    connect(addRoot, SIGNAL(triggered()), this, SLOT(openAddDialog()));
    popMenu->addAction(addRoot);

    if(item != NULL) {
        QAction *addNextNode = new QAction("添加子节点", this);
        QAction *delNode = new QAction("删除节点", this);

        connect(addNextNode, SIGNAL(triggered()), this, SLOT(openAddDialog()));

        popMenu->addAction(addNextNode);
        popMenu->addAction(delNode);
    }

    popMenu->exec(QCursor::pos());
    popMenu->deleteLater();
}
