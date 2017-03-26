#include "ruleeditdialog.h"
#include "ui_ruleeditdialog.h"

RuleEditDialog::RuleEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleEditDialog)
{
    ui->setupUi(this);

    class QValidator *validator=new QIntValidator(0,999999,this);
    ui->lineEdit_ruleID_2->setValidator(validator);

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
                                     QString paramID, int Judg, QString schemeID)
{
    ui->lineEdit_ruleID_2->setText(QString::number(ruleID));
    ui->lineEdit_errDesc->setText(errDesc);
    ui->lineEdit_detectTip->setText(detectTip);
    ui->lineEdit_paramID->setText(paramID);
    //todo Judg
    ui->lineEdit_schemeID->setText(schemeID);
}

void RuleEditDialog::on_pushButton_clicked()
{
    QSqlQuery query;

    if(m_mode == true) {
        // 添加
        QString sql = QString("INSERT INTO rule " \
                              "(ruleID, ErrDesc, detectTip, paramID, Judg, schemeID) "
                              "VALUES(%1, '%2', '%3', '%4', %5, '%6');")
                .arg(ui->lineEdit_ruleID_2->text().toInt())
                .arg(ui->lineEdit_errDesc->text())
                .arg(ui->lineEdit_detectTip->text())
                .arg(ui->lineEdit_paramID->text())
                .arg(0)
                .arg(ui->lineEdit_schemeID->text());


        qDebug() << "sql_1: " <<  sql;
        query.exec(sql);
    } else {
        // 编辑
        QString sql = QString("UPDATE rule SET " \
                              "ErrDesc='%1', detectTip='%2', " \
                              "paramID=%3, Judg=%4, " \
                              "schemeID='%5' WHERE ruleID=%6;")
                .arg(ui->lineEdit_errDesc->text())
                .arg(ui->lineEdit_detectTip->text())
                .arg(ui->lineEdit_paramID->text())
                .arg(0)
                .arg(ui->lineEdit_schemeID->text())
                .arg(ui->lineEdit_ruleID_2->text());

        qDebug() << "sql_2: " <<  sql;
        query.exec(sql);
    }

    this->close();
}
