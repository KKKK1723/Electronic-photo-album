#ifndef PICBUTTON_H
#define PICBUTTON_H

#include <QPushButton>
#include<QPixmap>//加载图片样式
#include<QEvent>
class PicButton : public QPushButton
{
public:
    PicButton(QWidget *parent = nullptr);
    void SetIcon(const QString& normal,const QString& hover,const QString& pressed);//正常 悬浮 点击 时的按钮图片样式


protected:
     bool event(QEvent *e) override;//通过这个事件e来判断是正常还是悬浮还是点击

private:
    void setNormalIcon();//正常
    void setHoverIcon();//悬浮
    void setPressedIcon();//点击
    QString _normal;
    QString _hover;
    QString _pressed;
};

#endif // PICBUTTON_H
