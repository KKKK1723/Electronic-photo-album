#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H

#include <QThread>
#include<QTreeWidget>

class ProTreeThread : public QThread
{
    Q_OBJECT//要写signal

public:
    ProTreeThread(const QString & src_path,const QString & dis_path,QTreeWidgetItem* parent_item,const int file_count,
                  QTreeWidget* self,QTreeWidgetItem* root,QObject *parent = nullptr);
    ~ProTreeThread();

protected:
    virtual void run();

//封装一个函数 run中调用这个函数
private:
    void CreateProTree(const QString& src_path,const QString& dist_path,QTreeWidgetItem* parent_item,int& file_count,
                       QTreeWidget* self, QTreeWidgetItem* root,QTreeWidgetItem* preitem=nullptr);


    //成员变量
    QString _src_path;//原地址
    QString _dist_path;//要复制到的地址
    int _file_count=0;
    QTreeWidgetItem* _parent_item;//父节点
    QTreeWidget* _self;//当前树
    QTreeWidgetItem* _root;
    bool _bstop;//控制线程退出

public:
    void SlotCanceled();
signals:
    void SigUpdateProgress(int);//更新进度的信号
    void SigFinishProgress(int);//完成
};

#endif // PROTREETHREAD_H
