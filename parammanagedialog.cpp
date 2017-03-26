#include "parammanagedialog.h"
#include "ui_parammanagedialog.h"
#include "parameditdialog.h"
#include "common.h"

ParamManageDialog::ParamManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamManageDialog)
{
    ui->setupUi(this);

    listDB();
}

ParamManageDialog::~ParamManageDialog()
{
    delete ui;
}

void ParamManageDialog::listDB()
{
    int row = 0;
    QSqlQuery query;
    QString sql = QString("SELECT * FROM parameter");

    query.exec(sql);
    while (query.next()) {
        int paramID = query.value("paramID").toInt();
        QString paramDesc = query.value("paramDesc").toString();
        int paramType = query.value("paramType").toInt();
        int upperLimit = query.value("upperLimit").toInt();
        int lowerLimit = query.value("lowerLimit").toInt();

        QTableWidgetItem *firstItem = new QTableWidgetItem(QString::number(paramID));
        firstItem->setData(DB_PARAM_PARAMID, paramID);
        firstItem->setData(DB_PARAM_PARAM_DESC, paramDesc);
        firstItem->setData(DB_PARAM_PARAM_TYPE, paramType);
        firstItem->setData(DB_PARAM_PARAM_UPPER_LIMIT, upperLimit);
        firstItem->setData(DB_PARAM_PARAM_LOWER_LIMIT, lowerLimit);

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(row, 0, firstItem);
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(paramDesc));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(paramType)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(upperLimit)));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(lowerLimit)));

        row++;
    }
}

void ParamManageDialog::on_addPushButton_clicked()
{
    ParamEditDialog *paramEditDialog = new ParamEditDialog();
    paramEditDialog->setMode(true);
    paramEditDialog->exec();

    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void ParamManageDialog::on_delPushButton_clicked()
{
    int currentRow = ui->tableWidget->currentIndex().row();
    QTableWidgetItem *firstItem = ui->tableWidget->item(currentRow, 0);
    if(firstItem == NULL)
        return;


    int paramID = firstItem->data(DB_PARAM_PARAMID).toInt();
    QString paramDesc = firstItem->data(DB_PARAM_PARAM_DESC).toString();

    QString title = QString("参数号[%1] %2").arg(paramID).arg(paramDesc);

    int status = QMessageBox::warning(this, "确认是否要删除",
                                      title, QMessageBox::Yes, QMessageBox::No);
    if(status == QMessageBox::Yes) {
        QSqlQuery query;
        QString sql = QString("DELETE FROM parameter WHERE paramID=%1").arg(paramID);
        query.exec(sql);
    }


    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void ParamManageDialog::on_editPushButton_clicked()
{
    int currentRow = ui->tableWidget->currentIndex().row();
    QTableWidgetItem *firstItem = ui->tableWidget->item(currentRow, 0);
    if(firstItem == NULL)
        return;


    int paramID = firstItem->data(DB_PARAM_PARAMID).toInt();
    QString paramDesc = firstItem->data(DB_PARAM_PARAM_DESC).toString();
    int paramType = firstItem->data(DB_PARAM_PARAM_TYPE).toInt();
    int upperLimit = firstItem->data(DB_PARAM_PARAM_UPPER_LIMIT).toInt();
    int lowerLimit = firstItem->data(DB_PARAM_PARAM_LOWER_LIMIT).toInt();

    ParamEditDialog *paramEditDialog = new ParamEditDialog();
    paramEditDialog->setMode(false);
    paramEditDialog->setParamEditData(paramID, paramDesc, paramType, upperLimit, lowerLimit);
    paramEditDialog->exec();

    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void ParamManageDialog::on_exitPushButton_clicked()
{
    this->close();
}
