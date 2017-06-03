#ifndef CENTERFORM_H
#define CENTERFORM_H

#include <QDebug>
#include <QWidget>
#include <QResizeEvent>
#include <QAxWidget>
#include <QProcess>

#include "zhenduanform.h"
#include "treemanageform.h"
#include "ruleform.h"
#include "fileform.h"

namespace Ui {
class CenterForm;
}

class CenterForm : public QWidget
{
    Q_OBJECT

public:
    explicit CenterForm(QWidget *parent = 0);
    ~CenterForm();

    void setLoginUsername(QString username);

    void setCurrentWidget(int index);

protected:
    void resizeEvent(QResizeEvent *event);
    void listNode();


private slots:
    void on_pushButton_account_2_clicked();
    void on_pushButton_word_clicked();
    void on_pushButton_Excel_clicked();
    void on_pushButton_calc_clicked();
    void on_pushButton_databank_clicked();
    void on_pushButton_datarecovry_clicked();

private:
    Ui::CenterForm *ui;
    QString login_username;

    ZhenDuanForm *zhenDuanForm;
    TreeManageForm *treeManageForm;
    RuleForm *ruleForm;
    FileForm *fileForm;
};

#endif // CENTERFORM_H
