#include "centerform.h"
#include "ui_centerform.h"


CenterForm::CenterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterForm)
{
    ui->setupUi(this);

    QWidget *zhenDuanWidget = ui->stackedWidget->widget(1);
    zhenDuanForm = new ZhenDuanForm(zhenDuanWidget);

    QWidget *treeManageWidget = ui->stackedWidget->widget(2);
    treeManageForm = new TreeManageForm(treeManageWidget);

    QWidget *ruleWidget = ui->stackedWidget->widget(3);
    ruleForm = new RuleForm(ruleWidget);
}

CenterForm::~CenterForm()
{
    delete ui;
}


void CenterForm::setCurrentWidget(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void CenterForm::resizeEvent(QResizeEvent *event)
{
    zhenDuanForm->setGeometry(0, 0, event->size().width(), event->size().height());
    treeManageForm->setGeometry(0, 0, event->size().width(), event->size().height());
    ruleForm->setGeometry(0, 0, event->size().width(), event->size().height());
}
