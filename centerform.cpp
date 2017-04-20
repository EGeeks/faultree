#include "centerform.h"
#include "ui_centerform.h"
#include "accountdialog.h"

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
    treeManageForm->setGeometry(0, 0, event->size().width(), event->size().height());
    ruleForm->setGeometry(0, 0, event->size().width(), event->size().height());
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
    QAxObject * documents = word.querySubObject("Documents");
    //documents->dynamicCall("Add (void)");
    //QAxObject * document = word.querySubObject("ActiveDocument");
}

// 打开Excel文档
void CenterForm::on_pushButton_Excel_clicked()
{
    //隐式的打开一个excel应用程序
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    //获取所有工作文档
    //QAxObject * workbooks = excel.querySubObject("WorkBooks");
    //创建一个excel文档
    // workbooks->dynamicCall("Add (void)");
    //获取当前激活的文档
    //QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取当前工作簿
}


// 打开计算器
void CenterForm::on_pushButton_calc_clicked()
{
    QProcess* process = new QProcess();
    QString CalcPath = "calc.exe";
    process->start(CalcPath);
}

