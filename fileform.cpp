#include "fileform.h"
#include "ui_fileform.h"


FileForm::FileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileForm)
{
    ui->setupUi(this);

    listFile();
}

FileForm::~FileForm()
{
    delete ui;
}

void FileForm::listFile()
{
    QString path = QDir::currentPath() + "\\database";

    model = new QFileSystemModel();
    model->setRootPath(path);

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(path));
}

void FileForm::on_pushButton_add_clicked()
{
    QString path = QDir::currentPath() + "\\database";
    QString fileName = QFileDialog::getOpenFileName(this, "添加文件", path);
    if(fileName != NULL) {
        qDebug() << "选择:" << fileName;

        QFileInfo fileinfo(fileName);
        QFile::copy(fileName, path + "\\" + fileinfo.fileName());
    }
}

void FileForm::on_pushButton_del_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid()) {
        return;
    }

    int status = QMessageBox::information(this,"Remove",QString("是否删除") + model->fileName(index),
                                          QMessageBox::Yes, QMessageBox::No);
    if(status == QMessageBox::Yes) {
        if (model->fileInfo(index).isDir()) {
            model->rmdir(index);
        } else {
            model->remove(index);
        }
    }
}
