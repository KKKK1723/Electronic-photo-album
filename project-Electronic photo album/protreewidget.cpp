#include "protreewidget.h"
#include<QDir>
#include "protreeitem.h"
#include "const.h"
ProTreeWidget::ProTreeWidget(QWidget *parent) {
    this->setHeaderHidden(true);//把数字隐藏掉
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
