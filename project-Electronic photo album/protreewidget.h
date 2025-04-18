#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>
#include<QAction>
#include<QProgressDialog>
#include"protreethread.h"
class ProTreeWidget : public QTreeWidget
{
public:
    ProTreeWidget(QWidget *parent = nullptr);
    void AddProTree(const QString &name,const QString &path);

private:
    QSet<QString> _set_path;//判断名字是否重复
    QTreeWidgetItem * _right_btn_item;
    QAction * _action_import;//导入
    QAction * _action_setstart;
    QAction * _action_closerpro;//关闭
    QAction * _action_slideshow;//轮播图播放
    QProgressDialog * _dialog_progress;//对话框
    std::shared_ptr<ProTreeThread>_thread_create_p;

private slots:
    void SlotItemPress(QTreeWidgetItem *item, int column);//点击时触发这个槽函数
    void SlotImport();
    void SlotUpdateProgress(int count);


};

#endif // PROTREEWIDGET_H
