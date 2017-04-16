#include "accountdialog.h"
#include "ui_accountdialog.h"
#include "common.h"

AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
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
        //        firstItem->setData(DB_USER_USERNAME, username);
        //        firstItem->setData(DB_USER_PASSWORD, password);
        //        firstItem->setData(DB_USER_DIAGNOSIS, diagnosis);
        //        firstItem->setData(DB_USER_TREE, treemanage);
        //        firstItem->setData(DB_USER_RULE, rulemanage);
        //        firstItem->setData(DB_USER_FILE, filemanage);
        //        firstItem->setData(DB_USER_FILE, system);

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

void AccountDialog::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();


    QSqlQuery query;
    QString sql = QString("SELECT * FROM user WHERE username == '%1' AND password='%2';")
            .arg(username)
            .arg(password);

    query.exec(sql);
    if(query.next()) {
        ListDB();
    } else {
        QMessageBox::warning(this, "登录", "用户名或密码不正确");
    }

}

void AccountDialog::on_pushButton_add_clicked()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(""));

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
}

void AccountDialog::on_pushButton_delete_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());

    ui->tableWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);
}

void AccountDialog::on_pushButton_modify_clicked()
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
}
