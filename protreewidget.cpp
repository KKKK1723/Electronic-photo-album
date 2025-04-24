#include "protreewidget.h"
#include<QDir>
#include "protreeitem.h"
#include "const.h"
#include<QGuiApplication>
#include<QMenu>
#include<QFileDialog>
#include"protreethread.h"
#include<QDebug>
#include"removeprodialog.h"
ProTreeWidget::ProTreeWidget(QWidget *parent):_active_item(nullptr),_right_btn_item(nullptr),_dialog_progress(nullptr),_selected_item(nullptr),
    _thread_create_p(nullptr),_thread_open_p(nullptr),_dialog_progress2(nullptr)
{
    this->setHeaderHidden(true);//把数字隐藏掉
    connect(this,&ProTreeWidget::itemPressed,this,&ProTreeWidget::SlotItemPress);//右键根目录打开菜单
    _action_import=new QAction(QIcon("qrc:/photo/1daeb62f494e3a0f040ea34c18cd41f.jpg"),tr("导入文件"),this);//this绑定父窗口 就不需要手动回收了
    _action_setstart=new QAction(QIcon("qrc:/photo/1daeb62f494e3a0f040ea34c18cd41f.jpg"),tr("设置此相册为活动相册"),this);
    _action_closerpro=new QAction(QIcon("qrc:/photo/1daeb62f494e3a0f040ea34c18cd41f.jpg"),tr("删除相册"),this);
    _action_slideshow=new QAction(QIcon("qrc:/photo/1daeb62f494e3a0f040ea34c18cd41f.jpg"),tr("轮播图播放"),this);

    connect(_action_import,&QAction::triggered,this,&ProTreeWidget::SlotImport);//点击导入文件后执行SlotImport函数
    connect(_action_setstart,&QAction::triggered,this,&ProTreeWidget::Slotsetstart);//点击设置活动文件后执行Slotsetstart函数
    connect(_action_closerpro,&QAction::triggered,this,&ProTreeWidget::Slotcloserpro);//点击删除相册后执行Slotcloserpro函数

    connect(this,&ProTreeWidget::itemDoubleClicked,this,&ProTreeWidget::SlotDoubleClickItem);

}


void ProTreeWidget::AddProTree(const QString &name, const QString &path)//创建相册到目录中
{
    QDir dir(path);
    QString _path=dir.absoluteFilePath(name);
    if(_set_path.find(_path)!=_set_path.end())//有这个路径了
    {
        return;
    }

    QDir p_dir(_path);
    if(!p_dir.exists())//不存在就创建
    {
        bool p=p_dir.mkpath(_path);
        if(!p)
        {
            return;//创建失败
        }
    }

    _set_path.insert(_path);
    auto item=new ProTreeItem(this,name,_path,TreeItemPro);
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/photo/OIP.jpg"));
    item->setData(0,Qt::ToolTipRole,_path);
    this->addTopLevelItem(item);
}

void ProTreeWidget::SlotItemPress(QTreeWidgetItem *item, int column)//右键打开菜单
{
    if(QGuiApplication::mouseButtons()&Qt::RightButton)//右键点击
    {
        //弹出一个菜单
        QMenu menu(this);//不需要menubar->addmenu 因为这是一个临时的 不是一个固定到顶部的全局的菜单项
        int itemtype=item->type();
        if(itemtype == TreeItemPro)//点击根目录才会弹出
        {
            _right_btn_item=item;
            menu.addAction(_action_import);
            menu.addAction(_action_setstart);
            menu.addAction(_action_closerpro);
            menu.addAction(_action_slideshow);
            menu.exec(QCursor::pos());//菜单弹出位置
        }
    }
}

void ProTreeWidget::SlotDoubleClickItem(QTreeWidgetItem *doubleitem, int col)
{
    if(QGuiApplication::mouseButtons()== Qt::LeftButton)
    {
        auto * tree_double =dynamic_cast<ProTreeItem*>(doubleitem);
        if(!tree_double)
        {
            return;
        }

        int itemtype=tree_double->type();
        if(itemtype==TreeItemPic)
        {
            emit SigUpdateSelected(tree_double->GetPath());
            _selected_item=doubleitem;
        }
    }
}

void ProTreeWidget::SlotImport()//菜单选项一  导入文件
{
    QFileDialog file_log;
    file_log.setFileMode(QFileDialog::Directory);//文件夹模式
    file_log.setViewMode(QFileDialog::Detail);//详细模式
    file_log.setWindowTitle(tr("选择导入文件夹"));
    QString file_log_path=dynamic_cast<ProTreeItem*>(_right_btn_item)->GetPath();
    file_log.setDirectory(file_log_path);//打开路径

    QStringList _list;
    if(file_log.exec())
    {
        _list=file_log.selectedFiles();//获取用户选中的文件然后存储在_list中
    }

    if(_list.length()<=0)//用户没有选择任何文件
    {
        return;
    }

    QString first_path=_list.at(0);
    int file_count=0;//记录文件中图片有多少个
    //主页面创建一个模态对话框显示加载进度
    _dialog_progress=new QProgressDialog(this);


    _thread_create_p =std::make_shared<ProTreeThread>(std::ref(first_path),std::ref(file_log_path),
                                                       _right_btn_item,file_count,this,_right_btn_item,nullptr);

     connect(_thread_create_p.get(),&ProTreeThread::SigUpdateProgress,this,&ProTreeWidget::SlotUpdateProgress);//连接的时候用裸指针

     connect(_thread_create_p.get(),&ProTreeThread::SigFinishProgress,this,&ProTreeWidget::SlotFinishProgress);//完成关闭窗口

     connect(_dialog_progress,&QProgressDialog::canceled,this,&ProTreeWidget::SlotCanceled);//点击取消按钮
     connect(this,&ProTreeWidget::SigCanceled,_thread_create_p.get(),&ProTreeThread::SlotCanceled);//取消通知线程


    _thread_create_p->start();

    //给对话框初始化
    _dialog_progress->setWindowTitle(tr("Please wait..."));
    _dialog_progress->setFixedWidth(PROGRESS_WIDTH);
    _dialog_progress->setRange(0,PROGRESS_WIDTH);
     _dialog_progress->exec();


}

void ProTreeWidget::Slotsetstart()//设置活动项目
{
   // qDebug()<<"!"<<Qt::endl;
    if(!_right_btn_item)
    {
        return;
    }

    QFont now_item_font;
    now_item_font.setBold(false);

    if(_active_item)//把之前的取消
    {
        _active_item->setFont(0,now_item_font);
    }

    now_item_font.setBold(true);
    _active_item=_right_btn_item;
    _active_item->setFont(0,now_item_font);

}

//删除相册
void ProTreeWidget::Slotcloserpro()
{
    RemoveProDialog remove_dialog;
    auto res=remove_dialog.exec();
    if(res!=QDialog::Accepted)
    {
        return;
    }

    bool is_remove=remove_dialog.IsRemove();//是否勾选

    auto now_tree_item=dynamic_cast<ProTreeItem*>(_right_btn_item);//此时点击的树目录  为了调用getpath
    auto path=now_tree_item->GetPath();
    //获取索引
    auto index_now_tree=this->indexOfTopLevelItem(_right_btn_item);



    //如果关闭了相册 此时右侧还显示相册中图片 那我们要清除
    auto *selectitem=dynamic_cast<ProTreeItem*>(_selected_item);
    //qDebug() << "_selected_item is null?" << (_selected_item == nullptr);
    //qDebug() << "selectitem is null?" << (selectitem == nullptr);
    if(selectitem&&now_tree_item==selectitem->GetRoot())
    {
        selectitem=nullptr;
        _selected_item=nullptr;
        emit SigClearPicShow();
        //qDebug()<<"fa";
    }

    //目录中删除
    delete this->takeTopLevelItem(index_now_tree);

    //容器中删除
    _set_path.remove(path);

    if(is_remove)
    {
        QDir dir(path);
        dir.removeRecursively();
    }

    _right_btn_item=nullptr;//因为已经删除
    if(now_tree_item==_active_item)
    {
        _active_item=nullptr;
    }



}

//进度条更新
void ProTreeWidget::SlotUpdateProgress(int count)
{
    //qDebug()<<"接收更新信号1"<<Qt::endl;
    if(!_dialog_progress)//未打开
    {
        return;
    }
   // qDebug()<<count<<Qt::endl;
    if(count>=PROGRESS_MAX)
    {
        _dialog_progress->setValue(count%PROGRESS_MAX);
    }
    else
    {
        _dialog_progress->setValue(count);
    }
}

//完成的时候关闭窗口就行
void ProTreeWidget::SlotFinishProgress()
{
    _dialog_progress->setValue(PROGRESS_MAX);
    _dialog_progress->deleteLater();
}

void ProTreeWidget::SlotCanceled()//通知线程取消
{
    emit SigCanceled();
     delete _dialog_progress;
     _dialog_progress=nullptr;
}

void ProTreeWidget::SlotUpdateProgress_open(int count)
{
    if(!_dialog_progress2)//未打开
    {
        return;
    }
    // qDebug()<<count<<Qt::endl;
    if(count>=PROGRESS_MAX)
    {
        _dialog_progress2->setValue(count%PROGRESS_MAX);
    }
    else
    {
        _dialog_progress2->setValue(count);
    }
}

void ProTreeWidget::SlotFinishProgress_open()
{
    _dialog_progress2->setValue(PROGRESS_MAX);
    _dialog_progress2->deleteLater();
}

void ProTreeWidget::SlotCanceled_open()
{
    emit SigCanceled_open();
    delete _dialog_progress2;
    _dialog_progress2=nullptr;
}

void ProTreeWidget::SlotOpenPro(const QString &path)//打开相册
{
    if(_set_path.find(path)!=_set_path.end())
    {
        return;//已经有了
    }

    _set_path.insert(path);
    int file_count=0;
    QDir dir(path);
    QString name=dir.dirName();//目录名称

    _thread_open_p=std::make_shared<OpenTreeThread>(path,file_count,this,nullptr);
   // _thread_open_p->start();
    _dialog_progress2=new QProgressDialog(this);
    connect(_thread_open_p.get(),&OpenTreeThread::SigUpdateProgress,this,&ProTreeWidget::SlotUpdateProgress_open);//连接的时候用裸指针

    connect(_thread_open_p.get(),&OpenTreeThread::SigFinishProgress,this,&ProTreeWidget::SlotFinishProgress_open);//完成关闭窗口

    connect(_dialog_progress2,&QProgressDialog::canceled,this,&ProTreeWidget::SlotCanceled_open);//点击取消按钮
    connect(this,&ProTreeWidget::SigCanceled_open,_thread_open_p.get(),&OpenTreeThread::SlotCanceled_open);//取消通知线程


    _thread_open_p->start();

    //给对话框初始化
    _dialog_progress2->setWindowTitle(tr("Please wait..."));
    _dialog_progress2->setFixedWidth(PROGRESS_WIDTH);
    _dialog_progress2->setRange(0,PROGRESS_WIDTH);
    _dialog_progress2->exec();
// qDebug()<<"1"<<Qt::endl;
}

void ProTreeWidget::SlotPreviousShow()
{
    if(!_selected_item)
    {
        return;
    }

    auto *curItem=dynamic_cast<ProTreeItem*>(_selected_item)->GetPreItem();
    if(!curItem)
    {
        return ;
    }

    emit SigUpdatePic_pre(curItem->GetPath());
    _selected_item=curItem;
    this->setCurrentItem(curItem);
}

void ProTreeWidget::SlotNextShow()
{
    if(!_selected_item)
    {
        return;
    }

    auto *curItem=dynamic_cast<ProTreeItem*>(_selected_item)->GetNextItem();
    if(!curItem)
    {
        return ;
    }

    emit SigUpdatePic_next(curItem->GetPath());
    _selected_item=curItem;
    this->setCurrentItem(curItem);
}


