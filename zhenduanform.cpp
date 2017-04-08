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

void ZhenDuanForm::on_treeWidget_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);

    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item == NULL) {
        return;
    }
    QString ErrDesc = item->data(0, DB_TREE_ERR_DESC).toString();
    ui->lineEdit_ErrDesc->setText(ErrDesc);
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


void ZhenDuanForm::on_pushButton_clicked()
{
    qDebug() << "start check";
    QSqlQuery query;
    QString sql;

    ui->textEdit->clear();

    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item == NULL) {
        ui->textEdit->setText("未选择设备树");
        return;
    }
    QString ErrDesc = item->data(0, DB_TREE_ERR_DESC).toString();
    QString ruleIDs = item->data(0, DB_TREE_RULE_ID).toString();
    ui->textEdit->append("故障: " + ErrDesc + "\n");

    foreach (QString ruleID, ruleIDs.split("#")) {

        // 1、满足“规则触发条件以A10001,”+“维修方案号0”条件默认已经触发（触发顺序见注）
        sql = QString("SELECT * FROM rule WHERE ruleID == %1")
                .arg(ruleID);
        query.exec(sql);
        if(query.next() == false) {
            ui->textEdit->append("非法规则号 : " + ruleID + "\n");
            continue;
        }

        QString detectTip = query.value("detectTip").toString();
        QString paramID = query.value("paramID").toString();
        QString Judg = query.value("Judg").toString();
        QString schemeID = query.value("schemeID").toString();
        ui->textEdit->append("检测提示: " + detectTip + "\n");

        // 3-1、如果维修方案号中出现如“W10002”时，
        // 出现对话框（“检测提示”内容和确定结束按钮，该规则号不被要求回答“是”或“否”）；
        if(schemeID != QString("0")) {
            ui->textEdit->append("回答: Yes\n");
            ui->textEdit->append("--------------");
            continue;
        }

        // 弹“检测提示内容”对话框，要求回答“是”或“否”；
        // 2、回答“是”或“否”后，将“故障描述”、“检测提示”、回答内容、分三行显示在诊断页面；
        QString JudyNext;
        int status = QMessageBox::information(this, "确认是或否",
                                              detectTip, QMessageBox::Yes, QMessageBox::No);
        if(status == QMessageBox::Yes) {
            JudyNext = Judg.replace("A", "Y");
            ui->textEdit->append("回答: Yes\n");
        } else {
            JudyNext = Judg.replace("A", "N");
            ui->textEdit->append("回答: No\n");
        }


        //3、回答完后，就有了“是#规则ID”或者“否#规则ID”检测是否触发下一条提示框：
        sql = QString("SELECT * FROM rule WHERE Judg == '%1';")
                .arg(JudyNext);
        query.exec(sql);
        if(query.next() == false) {
            ui->textEdit->append("数据库中未找到 规则: " + JudyNext);
            continue;
        }

        QString detectTip2 = query.value("detectTip").toString();
        QString paramID2 = query.value("paramID").toString();
        QString schemeID2 = query.value("schemeID").toString();
        ui->textEdit->append("检测提示: " + detectTip2 + "\n");
        if(paramID2 == QString("0")) {
            ui->textEdit->append("--------------");
            continue;
        }

        // 检测参数
        sql = QString("SELECT * FROM parameter WHERE paramID = '%1'").arg(paramID2);
        query.exec(sql);
        if(query.next() == false) {
            ui->textEdit->append("数据库中未找到 参数: " + paramID2);
            return;
        }
        QString paramDesc = query.value("paramDesc").toString();
        int upperLimit = query.value("upperLimit").toInt();
        int lowerLimit = query.value("lowerLimit").toInt();

        int value= QInputDialog::getInt(NULL, paramDesc, "参数");
        if(value > lowerLimit && value < upperLimit) {
            ui->textEdit->append("--------------");
            continue;
        }

        ui->textEdit->append("检测结束");
    }
}
