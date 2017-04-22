#include "accountdialog.h"
#include "ui_accountdialog.h"
#include "common.h"

AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountDialog)
{
    ui->setupUi(this);

    ListDB();

    modify_flag = false;
    ui->tableWidget->setEnabled(modify_flag);
}

AccountDialog::~AccountDialog()
{
    delete ui;
}

void AccountDialog::ListDB()
{
    int row = 0;
    QSqlQuery query;
    QString sql = QString("SELECT * FROM user");

    query.exec(sql);
    while (query.next()) {
        QString username = query.value("username").toString();
        QString password = query.value("password").toString();
        int diagnosis = query.value("diagnosis").toInt();
        int treemanage = query.value("treemanage").toInt();
        int rulemanage = query.value("rulemanage").toInt();
        int filemanage = query.value("filemanage").toInt();
        int system = query.value("system").toInt();

        QTableWidgetItem *firstItem = new QTableWidgetItem(QString::number(row));

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(row, 0, firstItem);
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(username));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(password));

        QTableWidgetItem *diagnosis_check = new QTableWidgetItem();
        diagnosis_check->setCheckState(diagnosis == 1 ? Qt::Checked : Qt::Unchecked);
        ui->tableWidget->setItem(row, 3, diagnosis_check);

        QTableWidgetItem *treemanage_check = new QTableWidgetItem();
        treemanage_check->setCheckState(treemanage == 1 ? Qt::Checked : Qt::Unchecked);
        ui->tableWidget->setItem(row, 4, treemanage_check);

        QTableWidgetItem *rulemanage_check = new QTableWidgetItem();
        rulemanage_check->setCheckState(rulemanage == 1 ? Qt::Checked : Qt::Unchecked);
        ui->tableWidget->setItem(row, 5, rulemanage_check);

        QTableWidgetItem *filemanage_check = new QTableWidgetItem();
        filemanage_check->setCheckState(filemanage == 1 ? Qt::Checked : Qt::Unchecked);
        ui->tableWidget->setItem(row, 6, filemanage_check);

        QTableWidgetItem *system_check = new QTableWidgetItem();
        system_check->setCheckState(system == 1 ? Qt::Checked : Qt::Unchecked);
        ui->tableWidget->setItem(row, 7, system_check);

        row++;
    }
}

void AccountDialog::on_pushButton_add_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "错误", "账号或者密码不能为空！");
        return;
    }

    QSqlQuery query;
    QString sql = QString("SELECT COUNT(1) as count FROM user WHERE username='%1';").arg(username);
    query.exec(sql);
    if(query.next() == false) {
        QMessageBox::warning(this, "错误", "数据库查询user 出错");
        return;
    }

    int count = query.value("count").toInt();
    if(count > 0) {
        QMessageBox::warning(this, "错误", "用户名重复");
        return;
    }

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(username));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(password));

    QTableWidgetItem *diagnosis_check = new QTableWidgetItem();
    diagnosis_check->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(row, 3, diagnosis_check);

    QTableWidgetItem *treemanage_check = new QTableWidgetItem();
    treemanage_check->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(row, 4, treemanage_check);

    QTableWidgetItem *rulemanage_check = new QTableWidgetItem();
    rulemanage_check->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(row, 5, rulemanage_check);

    QTableWidgetItem *filemanage_check = new QTableWidgetItem();
    filemanage_check->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(row, 6, filemanage_check);

    QTableWidgetItem *system_check = new QTableWidgetItem();
    system_check->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(row, 7, system_check);

    sql = QString("INSERT INTO user (username, password, diagnosis, treemanage, rulemanage, filemanage, system) " \
                  "VALUES ('%1', '%2', 0, 0, 0, 0, 0);")
            .arg(username)
            .arg(password);
    query.exec(sql);
}

void AccountDialog::on_pushButton_delete_clicked()
{
    int row = ui->tableWidget->currentRow();
    QString username = ui->tableWidget->item(row, 1)->text();
    ui->tableWidget->removeRow(row);


    qDebug() << "Delete" << username;

    QSqlQuery query;
    QString sql = QString("DELETE FROM user WHERE username='%1' ")
            .arg(username);
    query.exec(sql);
}

void AccountDialog::on_pushButton_modify_clicked()
{
    modify_flag = !modify_flag;
    ui->tableWidget->setEnabled(modify_flag);

    if(modify_flag == false)
        ui->pushButton_modify->setText("修改");
    else
        ui->pushButton_modify->setText("关闭修改");
}

void AccountDialog::on_tableWidget_clicked(const QModelIndex &index)
{
    int row = ui->tableWidget->currentRow();

    QString username = ui->tableWidget->item(row, 1)->text();
    QString password = ui->tableWidget->item(row, 2)->text();

    int diagnosis = ui->tableWidget->item(row, 3)->checkState() == Qt::Checked ? 1 : 0;
    int treemanage = ui->tableWidget->item(row, 4)->checkState() == Qt::Checked ? 1 : 0;
    int rulemanage = ui->tableWidget->item(row, 5)->checkState() == Qt::Checked ? 1 : 0;
    int filemanage = ui->tableWidget->item(row, 6)->checkState() == Qt::Checked ? 1 : 0;
    int system = ui->tableWidget->item(row, 7)->checkState() == Qt::Checked ? 1 : 0;

    QString sql = QString("UPDATE user SET password='%1', diagnosis=%2, treemanage=%3, " \
                          "rulemanage=%4, filemanage=%5, system=%6 WHERE username='%7'; ")
            .arg(password)
            .arg(diagnosis)
            .arg(treemanage)
            .arg(rulemanage)
            .arg(filemanage)
            .arg(system)
            .arg(username);

    QSqlQuery query;
    query.exec(sql);
}
