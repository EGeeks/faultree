#include "centerform.h"
#include "ui_centerform.h"
#include "accountdialog.h"
#include "mydb.h"

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

    QWidget *fileWidget = ui->stackedWidget->widget(4);
    fileForm = new FileForm(fileWidget);
}

CenterForm::~CenterForm()
{
    delete ui;
}

void CenterForm::setLoginUsername(QString username)
{
    login_username = username;
    zhenDuanForm->setLoginUsername(username);
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
    fileForm->setGeometry(0, 0, event->size().width(), event->size().height());
}


void CenterForm::on_pushButton_account_2_clicked()
{
    AccountDialog *accountDialog = new AccountDialog();
    accountDialog->show();
}

// 打开word
void CenterForm::on_pushButton_word_clicked()
{
    QAxWidget word("Word.Application");
    word.setProperty("Visible", true);
}

// 打开Excel文档
void CenterForm::on_pushButton_Excel_clicked()
{
    //隐式的打开一个excel应用程序
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
}


// 打开计算器
void CenterForm::on_pushButton_calc_clicked()
{
    QProcess* process = new QProcess();
    QString CalcPath = "calc.exe";
    process->start(CalcPath);
}


void CenterForm::on_pushButton_databank_clicked()
{
    bool ok;
    QString houzhou = QInputDialog::getText(this, tr("备份数据"),
                                            tr("文件后缀"), QLineEdit::Normal,
                                            QDir::home().dirName(), &ok);
    if (ok && !houzhou.isEmpty()) {
        QFileInfo fileinfo(DB_NAME);
        QFile::copy(DB_NAME, "database/" + fileinfo.baseName() + "-" + houzhou + "." +fileinfo.suffix());
    }
}

void CenterForm::on_pushButton_datarecovry_clicked()
{
    QString path = QDir::currentPath() + "/database";
    QString fileName = QFileDialog::getOpenFileName(this, "备份恢复", path, "*.sqlite");
    if(fileName != NULL) {
        //QFileInfo fileinfo(fileName);
        QFile::remove("tree.sqlite");
        QFile::copy(fileName, "tree.sqlite");
        qDebug() << "recorvy:" << fileName;
        QMessageBox::information(this, "备份恢复", "数据已恢复， 请重启软件");
    }
}
