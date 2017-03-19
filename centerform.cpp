#include "centerform.h"
#include "ui_centerform.h"


CenterForm::CenterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterForm)
{
    ui->setupUi(this);

    QWidget *zhenDuanWidget = ui->stackedWidget->widget(0);
    zhenDuanForm = new ZhenDuanForm(zhenDuanWidget);
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
}
