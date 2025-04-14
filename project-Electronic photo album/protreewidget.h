#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>

class ProTreeWidget : public QTreeWidget
{
public:
    ProTreeWidget(QWidget *parent = nullptr);
    void AddProTree(const QString &name,const QString &path);

private:
    QSet<QString> _set_path;//判断名字是否重复
};

#endif // PROTREEWIDGET_H
