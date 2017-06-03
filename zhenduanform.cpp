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

void ZhenDuanForm::setLoginUsername(QString username)
{
    logine_username = username;
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

bool ZhenDuanForm::checkRule(QString id)
{
    QSqlQuery query;
    QString sql;

    QString ruleID = id;

    while (1) {
        sql = QString("SELECT * FROM rule WHERE ruleID == %1")
                .arg(ruleID);
        query.exec(sql);
        if(query.next() == false) {
            ui->textEdit->append("非法规则号 : " + ruleID + "\n");
            break;
        }
        QString detectTip = query.value("detectTip").toString();
        QString paramID = query.value("paramID").toString();
        QString Judg = query.value("Judg").toString();
        QString schemeID = query.value("schemeID").toString();
        ui->textEdit->append("<b>检测提示:</b> " + detectTip);
        qDebug() << "===>> ruleID: " << ruleID << paramID << Judg;

        if(schemeID != "0") {
            qDebug() << "root find : " << schemeID;
            zhenduan_result = detectTip;
            printRepair(schemeID);
            // 打印维修信息
            return true;
        }

        QString JudyNext;
        bool ack;
        if(paramID == "0") {
            // 布尔型判断
            QMessageBox msgBox;
            msgBox.setWindowFlags(Qt::CustomizeWindowHint);
            msgBox.setText("确认是或否");
            msgBox.setInformativeText(detectTip);
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);

            int status = msgBox.exec();
            if(status == QMessageBox::Yes) {
                ack = true;
                JudyNext = "Y" + ruleID;
                ui->textEdit->append("<b>回答:</b> Yes");
            } else {
                ack = false;
                JudyNext = "N" + ruleID;
                ui->textEdit->append("<b>回答:<b> No");
            }
        } else {
            // 区间之内判断
            if(checkParam(paramID) == true) {
                ack = true;
                JudyNext = "Y" + ruleID;
            } else {
                ack = false;
                JudyNext = "N" + ruleID;
            }
        }

        ui->textEdit->append("\n");
        ruleID = findByJudy(JudyNext);
    }

    return false;
}

// 检测参数
bool ZhenDuanForm::checkParam(QString id)
{
    QSqlQuery query;
    QString sql;

    sql = QString("SELECT * FROM parameter WHERE paramID = '%1'").arg(id);
    query.exec(sql);
    if(query.next() == false) {
        ui->textEdit->append("数据库中未找到 参数: " + id);
        return false;
    }
    QString paramDesc = query.value("paramDesc").toString();
    QString paramType = query.value("paramType").toString();
    float upperLimit = query.value("upperLimit").toFloat();
    float lowerLimit = query.value("lowerLimit").toFloat();

    qDebug() << "upperLimit/lowerLimit" << upperLimit << lowerLimit;

    float value= QInputDialog::getInt(NULL, paramDesc, "参数");
    QString str = QString("<b>参数范围:</b>[%1%2, %3%4]")
            .arg(lowerLimit).arg(paramType).arg(upperLimit).arg(paramType);
    ui->textEdit->append(str);
    ui->textEdit->append("<b>输入:</b> " + QString::number(value) + paramType + "\n");
    if(value > lowerLimit && value < upperLimit) {
        return true;
    }

    return false;
}

QString ZhenDuanForm::findByJudy(QString Judy)
{
    QSqlQuery query;
    QString sql;

    sql = QString("SELECT * FROM rule WHERE Judg == '%1';")
            .arg(Judy);
    query.exec(sql);
    if(query.next() == false) {
        ui->textEdit->append("数据库中未找到 规则: " + Judy);
        return NULL;
    }

    return query.value("ruleID").toString();
}

void ZhenDuanForm::printRepair(QString schemeID)
{
    QSqlQuery query;
    QString sql;

    sql = QString("SELECT * FROM scheme WHERE schemeID == '%1';")
            .arg(schemeID);
    query.exec(sql);
    if(query.next() == false)
        return;

    QString repair = query.value("repair").toString();
    ui->textEdit->append("<b>维修方案号:</b> " + schemeID);
    ui->textEdit->append("<b>维修步骤:</b> \n");
    ui->textEdit->append(repair);
    ui->textEdit->append("\n");
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
    zhenduan_result.clear();
    ui->textEdit->clear();

    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item == NULL) {
        ui->textEdit->setText("未选择设备树");
        return;
    }
    QString ErrDesc = item->data(0, DB_TREE_ERR_DESC).toString();
    QString ruleIDs = item->data(0, DB_TREE_RULE_ID).toString();
    ui->textEdit->append("<b>诊断时间 : " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "</b>");
    ui->textEdit->append("<b>诊断人员 : </b>" + logine_username);
    ui->textEdit->append("<b>诊断故障名称: " + ErrDesc + "</b>");
    ui->textEdit->append("\n");

    ui->textEdit->append("<h4>诊断过程</h4>\n");
    ui->textEdit->append("\n");

    foreach (QString ruleID, ruleIDs.split("#")) {

        if(checkRule(ruleID) == true)
            break;
    }

    ui->textEdit->append("<b>检测结束</b>");
    ui->textEdit->append("\n");
    ui->textEdit->append("<b>诊断结果:</b>  " + zhenduan_result);
}

// PDF
void ZhenDuanForm::on_pushButton_baogao_clicked()
{
    QString pdfName = QDir::currentPath() + "/database" + "/" + ui->lineEdit_ErrDesc->text() + "-"
            + QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss") + ".pdf";

    QPrinter printer_text;
    printer_text.setPageSize(QPrinter::A4);  //设置纸张大小为A4
    printer_text.setOutputFormat(QPrinter::PdfFormat);
    printer_text.setOutputFileName(pdfName);//pdfname为要保存的pdf文件名

    QTextDocument text_document;
    QString html = ui->textEdit->toHtml();

    qDebug() << "PDF" << html;

    text_document.setHtml(html);
    text_document.print(&printer_text);
    text_document.end();
}
