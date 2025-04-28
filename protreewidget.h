#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>
#include<QAction>
#include<QProgressDialog>
#include"protreethread.h"
#include"opentreethread.h"


class SlidShowDlg;//声明一下  防止互相引用

class ProTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    ProTreeWidget(QWidget *parent = nullptr);
    void AddProTree(const QString &name,const QString &path);

private:
    QSet<QString> _set_path;//存入地址
    QTreeWidgetItem * _right_btn_item;//此时右键点击的条目
    QTreeWidgetItem * _active_item;//此时的活动条目
    QTreeWidgetItem * _selected_item;//点击的条目
    QAction * _action_import;//导入
    QAction * _action_setstart;
    QAction * _action_closerpro;//关闭
    QAction * _action_slideshow;//轮播图播放
    QProgressDialog * _dialog_progress;//对话框
    QProgressDialog * _dialog_progress2;//对话框
    std::shared_ptr<ProTreeThread>_thread_create_p;
    std::shared_ptr<OpenTreeThread>_thread_open_p;
    std::shared_ptr<SlidShowDlg>_slide_show_dlg;

private slots:
    void SlotItemPress(QTreeWidgetItem *item, int column);//点击时触发这个槽函数
    void SlotDoubleClickItem(QTreeWidgetItem* doubleitem,int col);
    void SlotImport();//导入
    void Slotsetstart();//活动
    void Slotcloserpro();//删除
    void SlotUpdateProgress(int count);
    void SlotFinishProgress();
    void SlotCanceled();

    void SlotUpdateProgress_open(int count);
    void SlotFinishProgress_open();
    void SlotCanceled_open();

    void SlotSlidShow();



public slots:
    void SlotOpenPro(const QString& path);//参数与信号一样

    void SlotPreviousShow();
    void SlotNextShow();

signals:
    void SigCanceled();//给线程发送取消信号
    void SigCanceled_open();
    void SigUpdateSelected(const QString& path);

    void SigUpdatePic_pre(const QString& path);
    void SigUpdatePic_next(const QString& path);

    void  SigClearPicShow();
};

#endif // PROTREEWIDGET_H
