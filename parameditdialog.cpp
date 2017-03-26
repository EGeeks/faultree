#include "parameditdialog.h"
#include "ui_parameditdialog.h"

ParamEditDialog::ParamEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamEditDialog)
{
    ui->setupUi(this);

    class QValidator *validator=new QIntValidator(0,999999,this);
    ui->lineEdit_paramID->setValidator(validator);
    ui->lineEdit_upperLimit->setValidator(validator);
    ui->lineEdit_lowLimit->setValidator(validator);
}

ParamEditDialog::~ParamEditDialog()
{
    delete ui;
}

void ParamEditDialog::setMode(bool mode)
{
    this->m_mode = mode;

    if(mode == false)
        ui->lineEdit_paramID->setEnabled(false);
}

void ParamEditDialog::setParamEditData(int paramID, QString paramDesc, int paramType,
                                       int upperLimit, int lowerLimit)
{
    ui->lineEdit_paramID->setText(QString::number(paramID));
    ui->lineEdit_paramDesc->setText(paramDesc);
    ui->lineEdit_paramType->setText(QString::number(paramType));
    ui->lineEdit_upperLimit->setText(QString::number(upperLimit));
    ui->lineEdit_lowLimit->setText(QString::number(lowerLimit));
}

void ParamEditDialog::on_pushButton_clicked()
{
    QSqlQuery query;

    if(m_mode == true) {
        // 添加
        QString sql = QString("INSERT INTO parameter " \
                              "(paramID, paramDesc, paramType, upperLimit, lowerLimit) "
                              "VALUES(%1, '%2', %3, %4, %5);")
                .arg(ui->lineEdit_paramID->text().toInt())
                .arg(ui->lineEdit_paramDesc->text())
                .arg(ui->lineEdit_paramType->text().toInt())
                .arg(ui->lineEdit_upperLimit->text().toInt())
                .arg(ui->lineEdit_lowLimit->text().toInt());

        qDebug() << "sql_1: " <<  sql;
        query.exec(sql);
    } else {
        // 编辑
        QString sql = QString("UPDATE parameter SET paramDesc='%1', " \
                              "paramType=%2, upperLimit=%3, lowerLimit=%4 " \
                              "WHERE paramID=%5;")
                .arg(ui->lineEdit_paramDesc->text())
                .arg(ui->lineEdit_paramType->text().toInt())
                .arg(ui->lineEdit_upperLimit->text().toInt())
                .arg(ui->lineEdit_lowLimit->text().toInt())
                .arg(ui->lineEdit_paramID->text().toInt());

        qDebug() << "sql_2: " <<  sql;
        query.exec(sql);
    }

    this->close();
}
