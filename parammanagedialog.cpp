#include "parammanagedialog.h"
#include "ui_parammanagedialog.h"

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

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(paramID)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(paramDesc));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(paramType)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(upperLimit)));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(lowerLimit)));

        row++;
    }
}

void ParamManageDialog::on_addPushButton_clicked()
{

}

void ParamManageDialog::on_delPushButton_clicked()
{

}

void ParamManageDialog::on_editPushButton_clicked()
{

}

void ParamManageDialog::on_exitPushButton_clicked()
{
    this->close();
}
