#ifndef PROTREEITEM_H
#define PROTREEITEM_H
#include<QTreeWidget>
#include<QTreeWidgetItem>

class ProTreeItem : public QTreeWidgetItem
{
public:

    //先写上 后面可能用
    ProTreeItem(QTreeWidget* view, const QString& name, const QString& path, int type=Type);
    ProTreeItem(QTreeWidgetItem* parent,const QString* name, const QString& path,QTreeWidget* root,int type=Type);
};

#endif // PROTREEITEM_H
