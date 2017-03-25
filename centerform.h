#ifndef CENTERFORM_H
#define CENTERFORM_H

#include <QDebug>
#include <QWidget>
#include <QResizeEvent>

#include "zhenduanform.h"
#include "treemanageform.h"

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


private:
    Ui::CenterForm *ui;

    ZhenDuanForm *zhenDuanForm;
    TreeManageForm *treeManageForm;
};

#endif // CENTERFORM_H
