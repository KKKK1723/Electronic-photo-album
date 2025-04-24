#ifndef PICSHOW_H
#define PICSHOW_H

#include <QDialog>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>

namespace Ui {
class PicShow;
}

class PicShow : public QDialog
{
    Q_OBJECT

public:
    explicit PicShow(QWidget *parent = nullptr);
    ~PicShow();
    void ReloadPic();//重绘

protected:
     bool event(QEvent *event) override;


private:
    void ShowPreNextBtns(bool b_show);
    void DisplayUpdate();//重绘更新图片

    Ui::PicShow *ui;
    QPropertyAnimation* _animation_show_pre;
    QPropertyAnimation* _animation_show_next;
    bool _b_show;//1 按钮显示 0 按钮隐藏
    QPixmap _pix_map;//加载的图片
    QPixmap Original_map;//原图
    QString _select_path;//加载的图片的地址

public slots:
    void SlotSelectItem(const QString& path);
    void SlotUpdate_previous_pic(const QString& path);
    void SlotUpdate_next_pic(const QString& path);
    void SlotClearnow();

signals:
    void SigPreviousClicked();//点击上一张 按钮
    void SigNextClicked();//点击下一张 按钮

};

#endif // PICSHOW_H
