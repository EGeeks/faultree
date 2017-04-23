#ifndef ZHENDUANFORM_H
#define ZHENDUANFORM_H

#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QTextBlock>
#include <QDateTime>

#include "common.h"

namespace Ui {
class ZhenDuanForm;
}


class ZhenDuanForm : public QWidget
{
    Q_OBJECT

public:
    explicit ZhenDuanForm(QWidget *parent = 0);
    ~ZhenDuanForm();

    void setLoginUsername(QString username);

protected:
    void listAllNode();
    void addSecondNode(QTreeWidgetItem *parentItem);
    void addThirdNode(QTreeWidgetItem *parentItem);

    void searchByKeyword(QString keyword);
    void searchByAlarmID(QString alarmID);

    bool checkRule(QString id);
    bool checkParam(QString id);
    QString findByJudy(QString Judy);
    void printRepair(QString schemeID);

private slots:
    void on_treeWidget_clicked(const QModelIndex &index);
    void on_radioButton_keyWord_toggled(bool checked);
    void on_radioButton_alarmID_toggled(bool checked);
    void on_lineEdit_search_textChanged(const QString &arg1);
    void on_pushButton_clicked();

    void on_pushButton_baogao_clicked();

private:
    Ui::ZhenDuanForm *ui;
    QString zhenduan_result;

    QString logine_username;
};

#endif // ZHENDUANFORM_H
