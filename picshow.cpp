#include "picshow.h"
#include "ui_picshow.h"

PicShow::PicShow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PicShow)
{
    ui->setupUi(this);
    ui->previousBtn->SetIcon(":/photo/previous.png",":/photo/previous_hover.png",":/photo/previous_press.png");
    ui->nextBtn->SetIcon(":/photo/next.png",":/photo/next_hover.png",":/photo/next_press.png");

    QGraphicsOpacityEffect* opacity_pre=new QGraphicsOpacityEffect(this);
    opacity_pre->setOpacity(0);//设置透明度
    QGraphicsOpacityEffect* opacity_next=new QGraphicsOpacityEffect(this);
    opacity_next->setOpacity(0);//设置透明度

    ui->previousBtn->setGraphicsEffect(opacity_pre);
    ui->nextBtn->setGraphicsEffect(opacity_next);

    _animation_show_pre=new QPropertyAnimation(opacity_pre,"opacity",this);
    _animation_show_pre->setEasingCurve(QEasingCurve::Linear);
    _animation_show_pre->setDuration(500);//动画时长

    _animation_show_next=new QPropertyAnimation(opacity_next,"opacity",this);
    _animation_show_next->setEasingCurve(QEasingCurve::Linear);
    _animation_show_next->setDuration(500);//动画时长

    connect(ui->previousBtn,&QPushButton::clicked,this,&PicShow::SigPreviousClicked);
    connect(ui->nextBtn,&QPushButton::clicked,this,&PicShow::SigNextClicked);
}

PicShow::~PicShow()
{
    delete ui;
}

bool PicShow::event(QEvent *event)//如果进入这个页面
{
    switch(event->type())
    {
        case QEvent::Enter:
        ShowPreNextBtns(true);
            break;
        case QEvent::Leave:
            ShowPreNextBtns(false);
            break;
        default:
            break;
    }

        return QDialog::event(event);
}

void PicShow::ReloadPic()//重绘
{
    // if(_select_path!="")
    // {
    //     const auto&width=ui->gridLayout->geometry().width();//获取矩形区域的宽
    //     const auto&height=ui->gridLayout->geometry().height();
    //     _pix_map.load(_select_path);
    //     _pix_map=_pix_map.scaled(width,height,Qt::KeepAspectRatio);
    //     ui->label->setPixmap(_pix_map);
    // }
    if (!Original_map.isNull()) {
       DisplayUpdate();
    }
}

void PicShow::ShowPreNextBtns(bool b_show)//
{
    //此时鼠标离开这个页面 并且按键是出现的
    if(!b_show&&_b_show)//显示状态------>隐藏状态
    {
        _animation_show_pre->stop();
        _animation_show_pre->setStartValue(1);
        _animation_show_pre->setEndValue(0);
        _animation_show_pre->start();

        _animation_show_next->stop();
        _animation_show_next->setStartValue(1);
        _animation_show_next->setEndValue(0);
        _animation_show_next->start();

        _b_show=false;//按钮已经隐藏
        return;
    }

    //此时鼠标在这个页面 并且按键是隐藏的
    if(b_show&&!_b_show)//隐藏状态------>显示状态
    {
        _animation_show_pre->stop();
        _animation_show_pre->setStartValue(0);
        _animation_show_pre->setEndValue(1);
        _animation_show_pre->start();

        _animation_show_next->stop();
        _animation_show_next->setStartValue(0);
        _animation_show_next->setEndValue(1);
        _animation_show_next->start();

        _b_show=true;//按钮已经隐藏
        return;
    }
}

void PicShow::DisplayUpdate()//更新状态
{
    // if (!ui || !ui->label) {
    //     qDebug() << "ui or label is nullptr!";
    //     return;
    // }
    if(!_select_path.isEmpty()&&!Original_map.isNull())
    {
        auto width=ui->gridLayout->geometry().width();
        auto height=ui->gridLayout->geometry().height();
        _pix_map=Original_map.scaled(width,height,Qt::KeepAspectRatio);
        ui->label->setPixmap(_pix_map);
       // qDebug()<<"1"<<Qt::endl;
    }
    // else
    // {
    //      qDebug()<<"2"<<Qt::endl;
    // }


}

void PicShow::SlotSelectItem(const QString &path)//首次图片
{
    // _select_path=path;
    // _pix_map.load(path);
    // auto width=this->width();
    // auto height=this->height();
    // _pix_map=_pix_map.scaled(width,height,Qt::KeepAspectRatio);
    // ui->label->setPixmap(_pix_map);
    _select_path = path;
    if(Original_map.load(path))
    {
        DisplayUpdate();
    }
}

void PicShow::SlotUpdate_previous_pic(const QString &path)
{
    _select_path=path;
    if(_select_path!="")
    {
        Original_map.load(_select_path);
        DisplayUpdate();
    }
}

void PicShow::SlotUpdate_next_pic(const QString &path)
{
    _select_path=path;
    if(_select_path!="")
    {
        Original_map.load(_select_path);
        DisplayUpdate();
    }
}

void PicShow::SlotClearnow()
{
    _select_path="";
    Original_map=QPixmap();
    _pix_map=QPixmap();
    if(ui->label)
    {
         ui->label->clear();
    }
   // qDebug() << "SlotClearnow called, _select_path = " << _select_path;

}
