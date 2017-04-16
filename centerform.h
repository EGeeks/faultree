#ifndef CENTERFORM_H
#define CENTERFORM_H

#include <QDebug>
#include <QWidget>
#include <QResizeEvent>

#include "zhenduanform.h"
#include "treemanageform.h"
#include "ruleform.h"

namespace Ui {
class CenterForm;
}

class CenterForm : public QWidget
{
    Q_OBJECT

public:
    explicit CenterForm(QWidget *parent = 0);
    ~CenterForm();

    void setCurrentWidget(int index);

protected:
    void resizeEvent(QResizeEvent *event);
    void listNode();


private slots:
    void on_pushButton_account_2_clicked();

private:
    Ui::CenterForm *ui;

    ZhenDuanForm *zhenDuanForm;
    TreeManageForm *treeManageForm;
    RuleForm *ruleForm;
};

#endif // CENTERFORM_H
