#include "schemeeditdialog.h"
#include "ui_schemeeditdialog.h"

SchemeEditDialog::SchemeEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SchemeEditDialog)
{
    ui->setupUi(this);
}

SchemeEditDialog::~SchemeEditDialog()
{
    delete ui;
}

void SchemeEditDialog::setMode(bool mode)
{
    this->m_mode = mode;

    if(mode == false)
        ui->lineEdit_schemeID->setEnabled(false);
}

void SchemeEditDialog::setRuleEditData(QString schemeID, QString schemeDesc, QString repair)
{
    ui->lineEdit_schemeID->setText(schemeID);
    ui->lineEdit_schemeDesc->setText(schemeDesc);
    ui->textEdit_repair->setText(repair);
}

void SchemeEditDialog::on_pushButton_clicked()
{
    QSqlQuery query;

    if(m_mode == true) {
        // 添加
        QString sql = QString("INSERT INTO scheme " \
                              "(schemeID, schemeDesc, repair) "
                              "VALUES('%1', '%2', '%3');")
                .arg(ui->lineEdit_schemeID->text())
                .arg(ui->lineEdit_schemeDesc->text())
                .arg(ui->textEdit_repair->toPlainText());


        qDebug() << "sql_1: " <<  sql;
        query.exec(sql);
    } else {
        // 编辑
        QString sql = QString("UPDATE scheme SET " \
                              "schemeDesc='%1', repair='%2' " \
                              "WHERE schemeID='%6';")
                .arg(ui->lineEdit_schemeDesc->text())
                .arg(ui->textEdit_repair->toPlainText())
                .arg(ui->lineEdit_schemeID->text());

        qDebug() << "sql_2: " <<  sql;
        query.exec(sql);
    }

    this->close();
}
