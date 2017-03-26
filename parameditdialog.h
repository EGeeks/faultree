#ifndef PARAMEDITDIALOG_H
#define PARAMEDITDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class ParamEditDialog;
}

class ParamEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParamEditDialog(QWidget *parent = 0);
    ~ParamEditDialog();

    void setMode(bool mode);
    void setParamEditData(int paramID, QString paramDesc, int paramType,
                          int upperLimit, int lowerLimit);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ParamEditDialog *ui;

    bool m_mode;  // true : 添加 false: 编辑
};

#endif // PARAMEDITDIALOG_H
