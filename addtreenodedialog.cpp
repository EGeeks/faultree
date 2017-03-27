#include "addtreenodedialog.h"
#include "ui_addtreenodedialog.h"

AddTreeNodeDialog::AddTreeNodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTreeNodeDialog)
{
    ui->setupUi(this);
    m_parentNodeID = 0;
    m_nodeID = 0;

    class QValidator *validator=new QIntValidator(0,999999,this);
    ui->lineEdit_nodeID->setValidator(validator);
    ui->lineEdit_errID->setValidator(validator);

    QRegExp rx;
    rx.setPattern("[0-9#]*");
    QValidator *validator1 = new QRegExpValidator(rx,this);
    ui->lineEdit_ruleID->setValidator(validator1);
}

AddTreeNodeDialog::~AddTreeNodeDialog()
{
    delete ui;
}

void AddTreeNodeDialog::setParentNodeID(int id)
{
    m_parentNodeID = id;
}

int AddTreeNodeDialog::getNodeID()
{
    return m_nodeID;
}

void AddTreeNodeDialog::on_CheckPushButton_clicked()
{
    int nodeID = ui->lineEdit_nodeID->text().toInt();
    QString ErrDesc = ui->lineEdit_ErrDesc->text();
    //int errID = ui->lineEdit_errID->text().toInt();
    QString ruleID = ui->lineEdit_ruleID->text();
    QString alarmID = ui->lineEdit_alarmID->text();

    QSqlQuery query;
    QString sql = QString("SELECT * FROM tree WHERE nodeID == %1")
            .arg(nodeID);

    query.exec(sql);
    int count = 0;
    while (query.next()) {
        count++;
    }
    if(count > 0) {
        ui->label_tishi->setText("节点ID 重复, 请使用其他");
        return;
    }

    if(ErrDesc.isEmpty() || ui->lineEdit_errID->text().isEmpty()
            || ruleID.isEmpty() || alarmID.isEmpty()) {
        ui->label_tishi->setText("请填写完整");
        return;
    }

    ui->label_tishi->setText("验证ok");
    ui->addPushButton->setEnabled(true);
}

void AddTreeNodeDialog::on_addPushButton_clicked()
{
    int nodeID = ui->lineEdit_nodeID->text().toInt();
    QString ErrDesc = ui->lineEdit_ErrDesc->text();
    int errID = ui->lineEdit_errID->text().toInt();
    QString ruleID = ui->lineEdit_ruleID->text();
    QString alarmID = ui->lineEdit_alarmID->text();


    QSqlQuery query;
    QString sql = QString("INSERT INTO tree " \
                          "(nodeID, parentNodeID, ErrID, ErrDesc, ruleID, alarmID) "
                          "VALUES(%1, %2, %3, '%4', '%5', '%6')")
            .arg(nodeID)
            .arg(m_parentNodeID)
            .arg(errID)
            .arg(ErrDesc)
            .arg(ruleID)
            .arg(alarmID);

    qDebug() << sql;

    query.exec(sql);
    this->close();

    m_nodeID = nodeID;
}
