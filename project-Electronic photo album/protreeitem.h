#ifndef PROTREEITEM_H
#define PROTREEITEM_H
#include<QTreeWidget>
#include<QTreeWidgetItem>

class ProTreeItem : public QTreeWidgetItem
{
public:

    //先写上 后面可能用
    ProTreeItem(QTreeWidget* view, const QString& name, const QString& path, int type=Type);
    ProTreeItem(QTreeWidgetItem* parent,const QString& name, const QString& path,QTreeWidgetItem* root,int type=Type);

//成员变量
private:
    QString _path;
    QString _name;
    QTreeWidgetItem * _root;
    QTreeWidgetItem * _pre_item;
    QTreeWidgetItem * _next_item;

};

#endif // PROTREEITEM_H
