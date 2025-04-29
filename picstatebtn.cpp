#include "picstatebtn.h"
#include"const.h"
#include<QEvent>

PicStateBtn::PicStateBtn(QWidget *parent):QPushButton(parent)
{

}

void PicStateBtn::SetIcon(const QString &normal, const QString &hover, const QString &pressed,
                          const QString &normal2, const QString &hover2, const QString &pressed2)
{
    _normal=normal;
    _hover=hover;
    _pressed=pressed;
    _normal2=normal2;
    _hover2=hover2;
    _pressed2=pressed2;

    QPixmap tmpPixmap;
    tmpPixmap.load(normal);
    this->resize(tmpPixmap.size());
    this->setIcon(tmpPixmap);
    this->setIconSize(tmpPixmap.size());
    _cur_state=PicBtnStateNormal;
}

bool PicStateBtn::event(QEvent *event)
{
    switch(event->type())
    {
        case QEvent::Enter:
        if(_cur_state<PicBtnStateNormal2)
        {
            setHoverIcon();
        }
        else
        {
            setHoverIcon2();
        }
        break;
        case QEvent::Leave:
            if(_cur_state<PicBtnStateNormal2)
            {
                setNormalIcon();
            }
            else
            {
                setNormalIcon2();
            }
            break;
        case QEvent::MouseButtonPress:
            if(_cur_state<PicBtnStateNormal2)
            {
                setPressIcon();
            }
            else
            {
                setPressIcon2();
            }
            break;
        case QEvent::MouseButtonRelease:
            if(_cur_state<PicBtnStateNormal2)
            {
                setHoverIcon2();
            }
            else
            {
                setHoverIcon();
            }
            break;
        default:
            break;
    }
        return QPushButton::event(event);
}

void PicStateBtn::setNormalIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_normal);
    this->setIcon(tmpPixmap);
    _cur_state=PicBtnStateNormal;
}

void PicStateBtn::setHoverIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_hover);
    this->setIcon(tmpPixmap);
    _cur_state=PicBtnStateHover;
}

void PicStateBtn::setPressIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_pressed);
    this->setIcon(tmpPixmap);
    _cur_state=PicBtnStatePress;
}

void PicStateBtn::setNormalIcon2()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_normal2);
    this->setIcon(tmpPixmap);
    _cur_state=PicBtnStateNormal2;
}

void PicStateBtn::setHoverIcon2()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_hover2);
    this->setIcon(tmpPixmap);
    _cur_state=PicBtnStateHover2;
}

void PicStateBtn::setPressIcon2()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_pressed2);
    this->setIcon(tmpPixmap);
    _cur_state=PicBtnStatePress2;
}

void PicStateBtn::SlotStart()
{
    setNormalIcon2();
}

void PicStateBtn::SlotStop()
{
    setNormalIcon();
}

