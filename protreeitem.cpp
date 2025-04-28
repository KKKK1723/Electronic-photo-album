#include "protreeitem.h"
#include"const.h"
ProTreeItem::ProTreeItem(QTreeWidget*view,const QString& name,
                         const QString& path,int type)
    :QTreeWidgetItem(view,type),_path(path),_name(name),_root(this),_pre_item(nullptr),_next_item(nullptr)
{

}

ProTreeItem:: ProTreeItem(QTreeWidgetItem* parent,const QString& name, const QString& path,QTreeWidgetItem* root,int type)
    :QTreeWidgetItem(parent,type),
    _path(path),_name(name),_root(root),_pre_item(nullptr),_next_item(nullptr)
{

}

//获取路径
const QString &ProTreeItem::GetPath()
{
    return _path;
}

//获取根目录
QTreeWidgetItem *  ProTreeItem::GetRoot()
{
    return _root;
}

//前向节点
void ProTreeItem::SetPreItem(QTreeWidgetItem *item)
{
    _pre_item=item;
}

//后向节点
void ProTreeItem::SetNextItem(QTreeWidgetItem *item)
{
    _next_item=item;
}

ProTreeItem *ProTreeItem::GetPreItem()
{
    return dynamic_cast<ProTreeItem*>(_pre_item);//从父类转为子类 QTreeWidgetItem * _pre_item;这个是QTreeWidgetItem，QTreeWidgetItem是ProTreeItem的基类
}

ProTreeItem *ProTreeItem::GetNextItem()
{
    return dynamic_cast<ProTreeItem*>(_next_item);//从父类转为子类
}

ProTreeItem *ProTreeItem::GetLastPicChild()//获取最后一个子节点
{
    if(this->type()==TreeItemPic)
    {
        return nullptr;
    }

    auto child_count=this->childCount();
    if(child_count==0)
    {
        return nullptr;
    }

    for(int i=child_count-1;i>=0;i--)
    {
        auto * last_child=this->child(i);
        auto * last_tree_child=dynamic_cast<ProTreeItem*>(last_child);
        if(last_tree_child->type()==TreeItemPic)//是图片
        {
            return last_tree_child;
        }

        //是文件夹
        last_child=last_tree_child->GetLastPicChild();
        if(!last_child)continue;

        last_tree_child=dynamic_cast<ProTreeItem*>(last_child);
        return last_tree_child;

    }
    return nullptr;

}

ProTreeItem *ProTreeItem::GetFirstPicChild()
{
    if(this->type()==TreeItemPic)
    {
        return nullptr;
    }

    auto child_count=this->childCount();
    if(child_count==0)
    {
        return nullptr;
    }

    for(int i=0;i<child_count-1;i++)
    {
        auto * first_child=this->child(i);
        auto * first_tree_child=dynamic_cast<ProTreeItem*>(first_child);
        if(first_tree_child->type()==TreeItemPic)//是图片
        {
            return first_tree_child;
        }

        //是文件夹
        first_child=first_tree_child->GetFirstPicChild();
        if(!first_child)continue;

        first_tree_child=dynamic_cast<ProTreeItem*>(first_child);
        return first_tree_child;

    }
    return nullptr;
}
