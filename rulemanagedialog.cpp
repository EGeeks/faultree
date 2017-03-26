#include "rulemanagedialog.h"
#include "ui_rulemanagedialog.h"
#include "ruleeditdialog.h"
#include "common.h"


RuleManageDialog::RuleManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleManageDialog)
{
    ui->setupUi(this);

    listDB();
}

// 显示数据库
void RuleManageDialog::listDB()
{
    int row = 0;
    QSqlQuery query;
    QString sql = QString("SELECT * FROM rule");

    query.exec(sql);
    while (query.next()) {
        int ruleID = query.value("ruleID").toInt();
        QString errDesc = query.value("errDesc").toString();
        QString detectTip = query.value("detectTip").toString();
        QString paramID = query.value("paramID").toString();
        int Judg = query.value("Judg").toInt();
        QString schemeID = query.value("schemeID").toString();

        QTableWidgetItem *firstItem = new QTableWidgetItem(QString::number(ruleID));
        firstItem->setData(DB_RULE_RULEID, ruleID);
        firstItem->setData(DB_RULE_ERR_DESC, errDesc);
        firstItem->setData(DB_RULE_DETECT_TIP, detectTip);
        firstItem->setData(DB_RULE_PARAMID, paramID);
        firstItem->setData(DB_RULE_JUDG, Judg);
        firstItem->setData(DB_RULE_SCHEMEID, schemeID);

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(row, 0, firstItem);
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(errDesc));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(detectTip));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(paramID));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(Judg)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(schemeID));

        row++;
    }
}

RuleManageDialog::~RuleManageDialog()
{
    delete ui;
}

void RuleManageDialog::on_addPushButton_clicked()
{
    RuleEditDialog *ruleEditDialog = new RuleEditDialog();
    ruleEditDialog->setMode(true);
    ruleEditDialog->exec();

    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void RuleManageDialog::on_delPushButton_clicked()
{
    int currentRow = ui->tableWidget->currentIndex().row();
    QTableWidgetItem *firstItem = ui->tableWidget->item(currentRow, 0);
    if(firstItem == NULL)
        return;


    int ruleID = firstItem->data(DB_RULE_RULEID).toInt();
    QString errDesc = firstItem->data(DB_RULE_ERR_DESC).toString();

    QString title = QString("规则号[%1] %2").arg(ruleID).arg(errDesc);

    int status = QMessageBox::warning(this, "确认是否要删除",
                                      title, QMessageBox::Yes, QMessageBox::No);
    if(status == QMessageBox::Yes) {
        QSqlQuery query;
        QString sql = QString("DELETE FROM rule WHERE ruleID=%1").arg(ruleID);
        query.exec(sql);
    }


    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void RuleManageDialog::on_editPushButton_clicked()
{
    int currentRow = ui->tableWidget->currentIndex().row();
    QTableWidgetItem *firstItem = ui->tableWidget->item(currentRow, 0);
    if(firstItem == NULL)
        return;


    int ruleID = firstItem->data(DB_RULE_RULEID).toInt();
    QString errDesc = firstItem->data(DB_RULE_ERR_DESC).toString();
    QString detectTip = firstItem->data(DB_RULE_DETECT_TIP).toString();
    QString paramID = firstItem->data(DB_RULE_PARAMID).toString();
    int Judg = firstItem->data(DB_RULE_JUDG).toInt();
    QString schemeID = firstItem->data(DB_RULE_SCHEMEID).toString();


    RuleEditDialog *ruleEditDialog = new RuleEditDialog();
    ruleEditDialog->setMode(false);
    ruleEditDialog->setRuleEditData(ruleID, errDesc, detectTip,
                                    paramID, Judg, schemeID);
    ruleEditDialog->exec();

    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void RuleManageDialog::on_exitPushButton_clicked()
{
    this->close();
}
