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

private:
    Ui::ZhenDuanForm *ui;
};

#endif // ZHENDUANFORM_H