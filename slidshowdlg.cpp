#include "slidshowdlg.h"
#include "ui_slidshowdlg.h"
#include"picanimationwid.h"
#include"PreListWid.h"
#include"protreewidget.h"
SlidShowDlg::SlidShowDlg(QWidget *parent, QTreeWidgetItem *first_item, QTreeWidgetItem *last_item)
    : QDialog(parent),_first_item(first_item),_last_item(last_item)
    , ui(new Ui::SlidShowDlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);

    ui->slidpreBtn->SetIcon(":/photo/previous.png",":/photo/previous_hover.png",":/photo/previous_press.png");
    ui->slidnextBtn->SetIcon(":/photo/next.png",":/photo/next_hover.png",":/photo/next_press.png");
    ui->closeBtn->SetIcon(":/photo/closeshow.png",":/photo/closeshow_hover.png",":/photo/closeshow_press.png");
    ui->playBtn->SetIcon(":/photo/play.png",":/photo/play_hover.png",":/photo/play_press.png",
                            ":/photo/pause.png",":/photo/pause_hover.png",":/photo/pause_press.png");


    connect(ui->slidnextBtn,&QPushButton::clicked,this,&SlidShowDlg::SlotSlidNext);
    connect(ui->slidpreBtn,&QPushButton::clicked,this,&SlidShowDlg::SlotSlidpre);

    connect(ui->preListWidget,&PreListWid::SigUpSelectShow,ui->picAnimation,&PicAnimationWid::SlotUpSelectShow);

    connect(ui->playBtn,&PicStateBtn::clicked,ui->picAnimation,&PicAnimationWid::SlotStartOrStop);

    connect(ui->picAnimation,&PicAnimationWid::SigStart,ui->playBtn,&PicStateBtn::SlotStart);
    connect(ui->picAnimation,&PicAnimationWid::SigStop,ui->playBtn,&PicStateBtn::SlotStop);

    auto * _protree_widget=dynamic_cast<ProTreeWidget*>(parent);
    connect(ui->picAnimation,&PicAnimationWid::SigStartMusic,_protree_widget,&ProTreeWidget::SlotStartMusic);
    connect(ui->picAnimation,&PicAnimationWid::SigStopMusic,_protree_widget,&ProTreeWidget::SlotStopMusic);

    auto* prelistWid=dynamic_cast<PreListWid*>(ui->preListWidget);
    connect(ui->picAnimation,&PicAnimationWid::SigUpPreList,prelistWid,&PreListWid::SlotUpPreList);
    connect(ui->picAnimation,&PicAnimationWid::SigSelectItem,prelistWid,&PreListWid::SlotUpSelect);



    ui->picAnimation->SetPixmap(_first_item);
    ui->picAnimation->Start();
}



SlidShowDlg::~SlidShowDlg()
{
    delete ui;
}

//关闭窗口
void SlidShowDlg::on_closeBtn_clicked()
{
    this->close();
}

void SlidShowDlg::SlotSlidNext()//切换下一张
{
    ui->picAnimation->SlidNext();
}

void SlidShowDlg::SlotSlidpre()
{
    ui->picAnimation->Slidpre();
}

