#ifndef PROTREE_H
#define PROTREE_H

#include <QDialog>
#include<QTreeWidget>
namespace Ui {
class ProTree;
}

class ProTree : public QDialog
{
    Q_OBJECT

public:
    explicit ProTree(QWidget *parent = nullptr);
    ~ProTree();
    QTreeWidget* GetTreeWidget();//获取当前在哪棵树



private:
    Ui::ProTree *ui;


public slots:
    void AddProTree(const QString name,const QString path);//回传名字和路径
};

#endif // PROTREE_H
