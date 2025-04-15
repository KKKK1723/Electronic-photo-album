#include "protreewidget.h"
#include<QDir>
#include "protreeitem.h"
#include "const.h"
#include<QGuiApplication>
#include<QMenu>
#include<QFileDialog>
ProTreeWidget::ProTreeWidget(QWidget *parent) {
    this->setHeaderHidden(true);//把数字隐藏掉
    connect(this,&ProTreeWidget::itemPressed,this,&ProTreeWidget::SlotItemPress);
    _action_import=new QAction(QIcon("qrc:/photo/1daeb62f494e3a0f040ea34c18cd41f.jpg"),tr("导入文件"),this);//this绑定父窗口 就不需要手动回收了
    _action_setstart=new QAction(QIcon("qrc:/photo/1daeb62f494e3a0f040ea34c18cd41f.jpg"),tr("设置活动相册"),this);
    _action_closerpro=new QAction(QIcon("qrc:/photo/1daeb62f494e3a0f040ea34c18cd41f.jpg"),tr("关闭相册"),this);
    _action_slideshow=new QAction(QIcon("qrc:/photo/1daeb62f494e3a0f040ea34c18cd41f.jpg"),tr("轮播图播放"),this);

    connect(_action_import,&QAction::triggered,this,&ProTreeWidget::SlotImport);

}

void ProTreeWidget::AddProTree(const QString &name, const QString &path)
{
    QDir dir(path);//指向这个路径
    QString file_path=dir.absoluteFilePath(name);//加上前面的名字 拼接起一个完整的路径
    if(_set_path.find(file_path)!=_set_path.end()){//找到了  表示重名了
        return;
    }

    QDir pro_dir(file_path);//用这个路径创建一个文件夹  看此文件夹是否存在
    if(!pro_dir.exists()){
        bool enable=pro_dir.mkpath(file_path);
        if(!enable){//不成功
            return;
        }
    }

    _set_path.insert(file_path);
    auto * item=new ProTreeItem(this,name,file_path,TreeItemPro);
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/photo/e94dcc6cc2a06e03229c65a6d1a7e70.jpg"));
    item->setData(0,Qt::ToolTipRole,file_path);//鼠标悬浮时提示文件路径
    this->addTopLevelItem(item);//加进来
}

void ProTreeWidget::SlotItemPress(QTreeWidgetItem *item, int column)
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

void ProTreeWidget::SlotImport()
{
    QFileDialog file_dialog;//创建一个文件对话框对象 file_dialog，用于打开或保存文件
    file_dialog.setFileMode(QFileDialog::Directory);//打开文件夹
    file_dialog.setWindowTitle(tr("选择导入的文件夹"));
    QString path="";

}
