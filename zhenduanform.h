#ifndef ZHENDUANFORM_H
#define ZHENDUANFORM_H

#include <QDebug>
#include <QSqlQuery>
#include <QWidget>
#include <QTreeWidgetItem>

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

protected:
    void listAllNode();
    void addSecondNode(QTreeWidgetItem *parentItem);
    void addThirdNode(QTreeWidgetItem *parentItem);

    void searchByKeyword(QString keyword);
    void searchByAlarmID(QString alarmID);

private slots:
    void on_radioButton_keyWord_toggled(bool checked);
    void on_radioButton_alarmID_toggled(bool checked);
    void on_lineEdit_search_textChanged(const QString &arg1);

private:
    Ui::ZhenDuanForm *ui;
};

#endif // ZHENDUANFORM_H
