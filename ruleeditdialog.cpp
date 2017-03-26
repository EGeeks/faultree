#include "ruleeditdialog.h"
#include "ui_ruleeditdialog.h"

RuleEditDialog::RuleEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleEditDialog)
{
    ui->setupUi(this);

    class QValidator *validator=new QIntValidator(0,999999,this);
    ui->lineEdit_ruleID_2->setValidator(validator);
    ui->lineEdit_depandErrID->setValidator(validator);
    ui->lineEdit_paramID->setValidator(validator);

    // 默认添加
    m_mode = true;
}

RuleEditDialog::~RuleEditDialog()
{
    delete ui;
}


void RuleEditDialog::setMode(bool mode)
{
    this->m_mode = mode;

    if(mode == false)
        ui->lineEdit_ruleID_2->setEnabled(false);
}

void RuleEditDialog::setRuleEditData(int ruleID, QString errDesc, QString detectTip,
                                     int depandErrID, int paramID, int Judg,
                                     QString errReason, QString Suggest)
{
    ui->lineEdit_ruleID_2->setText(QString::number(ruleID));
    ui->lineEdit_errDesc->setText(errDesc);
    ui->lineEdit_detectTip->setText(detectTip);
    ui->lineEdit_depandErrID->setText(QString::number(depandErrID));
    ui->lineEdit_paramID->setText(QString::number(paramID));
    //todo Judg
    ui->lineEdit_errReason->setText(errReason);
    ui->lineEdit_Suggest->setText(Suggest);
}

void RuleEditDialog::on_pushButton_clicked()
{
    QSqlQuery query;

    if(m_mode == true) {
        // 添加
        QString sql = QString("INSERT INTO rule " \
                              "(ruleID, ErrDesc, detectTip, depandErrID, paramID, Judg, errReason, Suggest) "
                              "VALUES(%1, '%2', '%3', %4, %5, %6, '%7', '%8');")
                .arg(ui->lineEdit_ruleID_2->text().toInt())
                .arg(ui->lineEdit_errDesc->text())
                .arg(ui->lineEdit_detectTip->text())
                .arg(ui->lineEdit_depandErrID->text().toInt())
                .arg(ui->lineEdit_paramID->text().toInt())
                .arg(0)
                .arg(ui->lineEdit_errReason->text())
                .arg(ui->lineEdit_Suggest->text());

        qDebug() << "sql_1: " <<  sql;
        query.exec(sql);
    } else {
        // 编辑
        QString sql = QString("UPDATE rule SET " \
                              "ErrDesc='%1', detectTip='%2', " \
                              "depandErrID=%3, paramID=%4, Judg=%5, " \
                              "errReason='%6', Suggest='%7' WHERE ruleID=%8;")
                .arg(ui->lineEdit_errDesc->text())
                .arg(ui->lineEdit_detectTip->text())
                .arg(ui->lineEdit_depandErrID->text().toInt())
                .arg(ui->lineEdit_paramID->text().toInt())
                .arg(0)
                .arg(ui->lineEdit_errReason->text())
                .arg(ui->lineEdit_Suggest->text())
                .arg(ui->lineEdit_ruleID_2->text().toInt());

        qDebug() << "sql_2: " <<  sql;
        query.exec(sql);
    }

    this->close();
}
