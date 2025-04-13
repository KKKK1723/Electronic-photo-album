#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenu>
#include<QAction>
#include<QDebug>
#include "wizard.h"
#define endl Qt::endl

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //创建菜单
    QMenu * menu_file=menuBar()->addMenu(tr("文件(&F)"));
    //创建设置菜单
    QMenu * menu_set=menuBar()->addMenu(tr("设置(&S)"));

    //新建
    QAction *act_creat_pro=new QAction(QIcon(":/photo/7a96a759b1e628c15d2992e8da2bebf.jpg"),tr("创建项目"),this);
    //快捷键
    act_creat_pro->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    menu_file->addAction(act_creat_pro);

    //打开
    QAction * act_open_pro=new QAction(QIcon(":/photo/e38198c26dc52b95a224af050b0951e.jpg"),tr("打开项目"),this);
    //快捷键
    act_open_pro->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menu_file->addAction(act_open_pro);


    //设置背景音乐
    QAction* act_music=new QAction(QIcon(":/music/bandicam 2025-04-13 14-51-23-941.mp3"),tr("背景音乐"),this);
    act_music->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    menu_set->addAction(act_music);


    //连接信号与槽  创建项目
    connect(act_creat_pro,&QAction::triggered,this,&MainWindow::SlotCreatePro);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotCreatePro(bool)
{
    qDebug()<<"slot create pro triggered"<<endl;
    Wizard wizard(this);//构造函数 父窗口设置为mainwindow
    wizard.setWindowTitle(tr("创建项目"));
    auto *page=wizard.page(0);//第一页
    page->setTitle(tr("创建项目配置"));
    //连接信号与槽 把项目配置传回来todo

    wizard.resize(500,300);
    //展示
    wizard.show();
    wizard.exec();
    //断开所有信号todo


}


