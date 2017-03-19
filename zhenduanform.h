#ifndef ZHENDUANFORM_H
#define ZHENDUANFORM_H

#include <QDebug>
#include <QSqlQuery>
#include <QWidget>
#include <QStandardItemModel>

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

private:
    Ui::ZhenDuanForm *ui;
};

#endif // ZHENDUANFORM_H
