#ifndef PRELISTWID_H
#define PRELISTWID_H

#include <QListWidget>
#include<QTreeWidgetItem>
class PreListWid : public QListWidget
{
public:
    PreListWid(QWidget *parent = nullptr);
    ~PreListWid();

private:
    QMap<QString,QListWidgetItem*>_set_items;
    void AddListItem(const QString& path);
    int _global;
    QPoint _pos_origin;
    int last_index;//上一次的位置
public slots:
    void SlotUpPreList(QTreeWidgetItem* tree_item);
    void SlotUpSelect(QTreeWidgetItem* tree_item);

};

#endif // PRELISTWID_H
