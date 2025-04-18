#ifndef PROTREEITEM_H
#define PROTREEITEM_H
#include<QTreeWidget>
#include<QTreeWidgetItem>

class ProTreeItem : public QTreeWidgetItem
{
public:

    //构造函数
    ProTreeItem(QTreeWidget* view, const QString& name, const QString& path, int type=Type);//创建顶层节点
    ProTreeItem(QTreeWidgetItem* parent,const QString& name, const QString& path,QTreeWidgetItem* root,int type=Type);//给某个节点添加子项

    const QString& GetPath();//获取路径
    QTreeWidgetItem* GetRoot();//获取根目录
    void SetPreItem(QTreeWidgetItem* item);//前
    void SetNextItem(QTreeWidgetItem* item);//后
    ProTreeItem* GetPreItem();//前一个
    ProTreeItem* GetNextItem();//下一个
    ProTreeItem* GetLastPicChild();
    ProTreeItem* GetFirstPicChild();

//成员变量
private:
    QString _path;//当前节点路径
    QString _name;//当前节点名称
    QTreeWidgetItem * _root;//当前节点的根目录
    QTreeWidgetItem * _pre_item;//前一个节点
    QTreeWidgetItem * _next_item;//后一个节点

};

#endif // PROTREEITEM_H
