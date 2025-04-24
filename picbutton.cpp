#include "picbutton.h"



PicButton::PicButton(QWidget *parent)
{

}

void PicButton::SetIcon(const QString &normal, const QString &hover, const QString &pressed)
{
    _normal=normal;
    _hover=hover;
    _pressed=pressed;

    QPixmap tmpPixmp;
    tmpPixmp.load(normal);
    this->resize(tmpPixmp.size());
    this->setIcon(tmpPixmp);
    this->setIconSize(tmpPixmp.size());
}

bool PicButton::event(QEvent *e)
{
    switch(e->type())
    {
        case QEvent::Enter:
            setHoverIcon();
            break;
        case QEvent::Leave:
            setNormalIcon();
                break;
        case QEvent::MouseButtonPress:
            setPressedIcon();
            break;
        case QEvent::MouseButtonRelease:
            setHoverIcon();
            break;
        default:
            break;
    }

        return QPushButton::event(e);
}

void PicButton::setNormalIcon()
{
    QPixmap tmpPixmp;
    tmpPixmp.load(_normal);
    this->setIcon(tmpPixmp);

}

void PicButton::setHoverIcon()
{
    QPixmap tmpPixmp;
    tmpPixmp.load(_hover);
    this->setIcon(tmpPixmp);
}

void PicButton::setPressedIcon()
{
    QPixmap tmpPixmp;
    tmpPixmp.load(_pressed);
    this->setIcon(tmpPixmp);
}
