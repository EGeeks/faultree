#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 打开数据库
    createDB();

    // 设置状态栏
    label1 = new QLabel(this);
    label1->setText("[欢迎使用数控机床人机交互系统]");
    label2 = new QLabel(this);
    label2->setText("当前用户");
    ui->statusbar->addWidget(label1);
    ui->statusbar->addWidget(label2);
    m_statusbarTimeID = startTimer(1000);


    ui->menubar->hide();

    login = new Login();
    connect(login, SIGNAL(checkPass(QString)), this, SLOT(on_LoginPass(QString)));
    login->show();

    // 加载核心区控件
    centerForm = new CenterForm(ui->centralwidget);
    centerForm->setGeometry(QRect(0, 0, 1019, 581));

    // 显示首页
    centerForm->setCurrentWidget(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoginPass(QString username)
{
    m_currUsername = username;
    login->close();
    this->show();
}


void MainWindow::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_statusbarTimeID) {
        // 定时更新状态栏时间
        QString time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
        label2->setText("当前用户:" + m_currUsername + " 当前时间: " + time);
    }
}

void MainWindow::on_actionHome_triggered()
{
    centerForm->setCurrentWidget(0);
}

void MainWindow::on_zhenduanAction_triggered()
{
    centerForm->setCurrentWidget(1);
}

void MainWindow::on_treeMangeAction_triggered()
{
    centerForm->setCurrentWidget(2);
}

void MainWindow::on_ruleAction_triggered()
{
    centerForm->setCurrentWidget(3);
}

void MainWindow::on_fileAction_triggered()
{
    centerForm->setCurrentWidget(4);
}

void MainWindow::on_maintrainAction_triggered()
{
    centerForm->setCurrentWidget(5);
}

void MainWindow::on_helpToolAction_triggered()
{
    centerForm->setCurrentWidget(6);
}

void MainWindow::createDB()
{
    MyDB::get_instance()->connect();

    if(MyDB::get_instance()->isConnOK() == false) {
        QMessageBox::warning(NULL, "错误", "数据库连接失败");
        return;
    }

    QSqlQuery query;
    bool bsuccess;

    /*
     *  tree 表
     *  nodeID   节点ID
     *  ErrID    故障ID
     *  ErrDesc  节点名称
     *  ruleID   对应规则ID
     *  alarmID  报警号ID
     */
    bsuccess = query.exec("create table IF NOT EXISTS tree " \
                          "(nodeID INTEGER unique, parentNodeID INTEGER, " \
                          "ErrID INTEGER, ErrDesc TEXT, " \
                          "ruleID TEXT, alarmID TEXT)");
    if(bsuccess == false) {
        QMessageBox::warning(NULL, "错误", "数据库创建tree失败");
    }

    /*
     *  rule 表
     *  ruleID      规则ID
     *  ErrDesc     故障信息
     *  detectTip   检测提示
     *  paramID     参数ID
     *  Judg        判断标准
     *  schemeID    维修方案号
     */
    bsuccess = query.exec("create table IF NOT EXISTS rule " \
                          "(ruleID INTEGER unique, ErrDesc TEXT, detectTip TEXT, " \
                          "paramID TEXT, Judg TEXT, schemeID TEXT)");
    if(bsuccess == false) {
        QMessageBox::warning(NULL, "错误", "数据库创建rule失败");
    }

    /*
     *  parameter 表
     *  paramID     参数ID
     *  paramDesc   参数信息
     *  paramType   参数类型
     *  upperLimit  上限
     *  lowerLimit  下限
     */
    bsuccess = query.exec("create table IF NOT EXISTS parameter" \
                          "(paramID INTEGER unique, paramDesc TEXT, paramType INTEGER, " \
                          "upperLimit INTEGER, lowerLimit INTEGER)");
    if(bsuccess == false) {
        QMessageBox::warning(NULL, "错误", "数据库创建parameter失败");
    }


    /*
     *  scheme 表
     *  schemeID    方案ID
     *  schemeDesc  方案描述
     *  repair      维修步骤
     */
    bsuccess = query.exec("create table IF NOT EXISTS scheme" \
                          "(schemeID TEXT unique, schemeDesc TEXT, repair TEXT)");
    if(bsuccess == false) {
        QMessageBox::warning(NULL, "错误", "数据库创建parameter失败");
    }
}

// 退出按钮触发
void MainWindow::on_exitAction_triggered()
{
    int status = QMessageBox::warning(this, "确认",
                                      "确定退出？", QMessageBox::Yes, QMessageBox::No);

    if(status == QMessageBox::Yes)
        this->close();
}
