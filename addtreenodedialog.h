#ifndef ADDTREENODEDIALOG_H
#define ADDTREENODEDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class AddTreeNodeDialog;
}

class AddTreeNodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTreeNodeDialog(QWidget *parent = 0);
    ~AddTreeNodeDialog();

    void setParentNodeID(int id);
    int getNodeID();

private slots:
    void on_CheckPushButton_clicked();
    void on_addPushButton_clicked();

private:
    Ui::AddTreeNodeDialog *ui;
    int m_parentNodeID;
    int m_nodeID;

};

#endif // ADDTREENODEDIALOG_H
