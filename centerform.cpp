#include "centerform.h"
#include "ui_centerform.h"

CenterForm::CenterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CenterForm)
{
    ui->setupUi(this);
}

CenterForm::~CenterForm()
{
    delete ui;
}


void CenterForm::setCurrentWidget(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
