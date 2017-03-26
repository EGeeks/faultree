#include "schememanagedialog.h"
#include "ui_schememanagedialog.h"
#include "schemeeditdialog.h"
#include "common.h"

SchemeManageDialog::SchemeManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchemeManageDialog)
{
    ui->setupUi(this);

    listDB();
}

SchemeManageDialog::~SchemeManageDialog()
{
    delete ui;
}

// 显示数据库
void SchemeManageDialog::listDB()
{
    int row = 0;
    QSqlQuery query;
    QString sql = QString("SELECT * FROM scheme");

    query.exec(sql);
    while (query.next()) {
        QString schemeID = query.value("schemeID").toString();
        QString schemeDesc = query.value("schemeDesc").toString();
        QString repair = query.value("repair").toString();


        QTableWidgetItem *firstItem = new QTableWidgetItem(schemeID);
        firstItem->setData(DB_SCHEME_ID, schemeID);
        firstItem->setData(DB_SCHEME_DESC, schemeDesc);
        firstItem->setData(DB_SCHEME_REPAIR, repair);


        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(row, 0, firstItem);
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(schemeDesc));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(repair));

        row++;
    }
}

void SchemeManageDialog::on_addPushButton_clicked()
{
    SchemeEditDialog *schemeEditDialog = new SchemeEditDialog();
    schemeEditDialog->setMode(true);
    schemeEditDialog->exec();

    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void SchemeManageDialog::on_editPushButton_clicked()
{
    int currentRow = ui->tableWidget->currentIndex().row();
    QTableWidgetItem *firstItem = ui->tableWidget->item(currentRow, 0);
    if(firstItem == NULL)
        return;

    QString schemeID = firstItem->data(DB_SCHEME_ID).toString();
    QString schemeDesc = firstItem->data(DB_SCHEME_DESC).toString();
    QString repair = firstItem->data(DB_SCHEME_REPAIR).toString();


    SchemeEditDialog *schemeEditDialog = new SchemeEditDialog();
    schemeEditDialog->setMode(false);
    schemeEditDialog->setRuleEditData(schemeID, schemeDesc, repair);
    schemeEditDialog->exec();

    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void SchemeManageDialog::on_delPushButton_clicked()
{
    int currentRow = ui->tableWidget->currentIndex().row();
    QTableWidgetItem *firstItem = ui->tableWidget->item(currentRow, 0);
    if(firstItem == NULL)
        return;


    QString schemeID = firstItem->data(DB_SCHEME_ID).toString();
    QString schemeDesc = firstItem->data(DB_SCHEME_DESC).toString();

    QString title = QString("维修方案号[%1] %2").arg(schemeID).arg(schemeDesc);

    int status = QMessageBox::warning(this, "确认是否要删除",
                                      title, QMessageBox::Yes, QMessageBox::No);
    if(status == QMessageBox::Yes) {
        QSqlQuery query;
        QString sql = QString("DELETE FROM scheme WHERE schemeID='%1'").arg(schemeID);
        query.exec(sql);
    }


    // 刷新tab
    int len = ui->tableWidget->rowCount();
    for(int i = 0; i < len; i++)
        ui->tableWidget->removeRow(0);
    listDB();
}

void SchemeManageDialog::on_exitPushButton_clicked()
{
    this->close();
}
