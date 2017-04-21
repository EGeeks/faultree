#ifndef FILEFORM_H
#define FILEFORM_H

#include <QDebug>
#include <QFile>
#include <QWidget>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>

namespace Ui {
class FileForm;
}

class FileForm : public QWidget
{
    Q_OBJECT

public:
    explicit FileForm(QWidget *parent = 0);
    ~FileForm();

    void listFile();

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_del_clicked();

private:
    Ui::FileForm *ui;
    QFileSystemModel *model;
};

#endif // FILEFORM_H
