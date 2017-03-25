#include "addtreenodedialog.h"
#include "ui_addtreenodedialog.h"

AddTreeNodeDialog::AddTreeNodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTreeNodeDialog)
{
    ui->setupUi(this);
}

AddTreeNodeDialog::~AddTreeNodeDialog()
{
    delete ui;
}
