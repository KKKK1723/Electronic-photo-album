#ifndef PICSTATEBTN_H
#define PICSTATEBTN_H

#include <QPushButton>

class PicStateBtn : public QPushButton
{
    Q_OBJECT
public:
    PicStateBtn(QWidget *parent = nullptr);
    void SetIcon(const QString& normal,const QString& hover,const QString& pressed,//正常1 悬浮1 点击1 时的按钮图片样式
                 const QString& normal2,const QString& hover2,const QString& pressed2);//正常2 悬浮2 点击2 时的按钮图片样式

protected:
    bool event(QEvent *e) override;

private:
    void setNormalIcon();
    void setHoverIcon();
    void setPressIcon();

    void setNormalIcon2();
    void setHoverIcon2();
    void setPressIcon2();

    QString _normal;
    QString _hover;
    QString _pressed;
    QString _normal2;
    QString _hover2;
    QString _pressed2;
    int _cur_state;

public slots:
    void SlotStart();
    void SlotStop();
};

#endif // PICSTATEBTN_H
