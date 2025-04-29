#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenu>
#include<QAction>
#include<QDebug>
#include "wizard.h"
#include "protree.h"
#include<QFileDialog>
#include "protreewidget.h"
#include"picshow.h"
#define endl Qt::endl

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    this->setMinimumSize(480,240);
    ui->setupUi(this);

    //创建菜单
    QMenu * menu_file=menuBar()->addMenu(tr("文件(&F)"));
    //创建设置菜单
    QMenu * menu_set=menuBar()->addMenu(tr("设置(&S)"));

    //新建
    QAction *act_creat_pro=new QAction(QIcon(":/photo/7a96a759b1e628c15d2992e8da2bebf.jpg"),tr("创建相册"),this);
    //快捷键
    act_creat_pro->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    menu_file->addAction(act_creat_pro);

    //打开
    QAction * act_open_pro=new QAction(QIcon(":/photo/e38198c26dc52b95a224af050b0951e.jpg"),tr("打开相册"),this);
    //快捷键
    act_open_pro->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menu_file->addAction(act_open_pro);


    //设置背景音乐
    QAction* act_music=new QAction(QIcon(":/music/bandicam 2025-04-13 14-51-23-941.mp3"),tr("播放背景音乐"),this);
    act_music->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    menu_set->addAction(act_music);


    //连接信号与槽  创建项目
    connect(act_creat_pro,&QAction::triggered,this,&MainWindow::SlotCreatePro);

    //打开相册
    connect(act_open_pro,&QAction::triggered,this,&MainWindow::SlotOpenPro);


    //左侧加入目录树
    _protree=new ProTree();
    ui->proLayout->addWidget(_protree);

    auto tree=dynamic_cast<ProTree*>(_protree)->GetTreeWidget();
    auto treewidget=dynamic_cast<ProTreeWidget*>(tree);
    connect(this,&MainWindow::SigOpenPro,treewidget,&ProTreeWidget::SlotOpenPro);

    //右侧图片区
    _picshow=new PicShow();
    ui->picLayout->addWidget(_picshow);
    auto * pro_picshow=dynamic_cast<PicShow*>(_picshow);
    connect(treewidget,&ProTreeWidget::SigUpdateSelected,pro_picshow,&PicShow::SlotSelectItem);

    connect(pro_picshow,&PicShow::SigPreviousClicked,treewidget,&ProTreeWidget::SlotPreviousShow);
    connect(pro_picshow,&PicShow::SigNextClicked,treewidget,&ProTreeWidget::SlotNextShow);
    connect(treewidget,&ProTreeWidget::SigUpdatePic_pre,pro_picshow,&PicShow::SlotUpdate_previous_pic);
    connect(treewidget,&ProTreeWidget::SigUpdatePic_next,pro_picshow,&PicShow::SlotUpdate_next_pic);

    connect(treewidget,&ProTreeWidget::SigClearPicShow,pro_picshow,&PicShow::SlotClearnow);


    connect(act_music,&QAction::triggered,treewidget,&ProTreeWidget::SlotSetMusic);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)//重绘事件
{
     auto *pro_pic_show=dynamic_cast<PicShow*>(_picshow);
    pro_pic_show->ReloadPic();
   return QMainWindow::resizeEvent(event);
}

void MainWindow::SlotCreatePro(bool)
{
    //qDebug()<<"slot create pro triggered"<<endl;
    Wizard wizard(this);//构造函数 父窗口设置为mainwindow
    wizard.setWindowTitle(tr("创建相册"));
    auto *page=wizard.page(0);//第一页
    page->setTitle(tr("相册名称与存放路径"));
    //连接信号与槽 把项目配置传回来todo
    connect(&wizard,&Wizard::SigProSettings,dynamic_cast<ProTree*>(_protree),&ProTree::AddProTree);
    wizard.resize(600,400);
    //展示
    wizard.show();
    wizard.exec();
    //断开所有信号todo
    disconnect();

}

void MainWindow::SlotOpenPro(bool)
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);//目录模式
    file_dialog.setWindowTitle(tr("选择导入的文件夹"));
    file_dialog.setDirectory(QDir::currentPath());
    file_dialog.setViewMode(QFileDialog::Detail);

    QStringList file_list;
    if(file_dialog.exec())
    {
        file_list=file_dialog.selectedFiles();//选中的文件
    }

    if(file_list.length()<=0)
    {
        return;
    }

    QString path=file_list.at(0);
    emit SigOpenPro(path);//导入的路径
}


