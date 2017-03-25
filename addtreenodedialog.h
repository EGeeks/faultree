#ifndef ADDTREENODEDIALOG_H
#define ADDTREENODEDIALOG_H

#include <QDialog>

namespace Ui {
class AddTreeNodeDialog;
}

class AddTreeNodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTreeNodeDialog(QWidget *parent = 0);
    ~AddTreeNodeDialog();

private:
    Ui::AddTreeNodeDialog *ui;
};

#endif // ADDTREENODEDIALOG_H
