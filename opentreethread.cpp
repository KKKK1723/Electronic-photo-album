#include "opentreethread.h"
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include<QDir>
#include"protreeitem.h"
#include"const.h"
OpenTreeThread::OpenTreeThread(const QString src_path, int file_count, QTreeWidget *self, QObject *parent)
    :_src_path(src_path),_file_count(file_count),_self(self),QThread(parent),_bstop(false),_root(nullptr)
{


}

void OpenTreeThread::OpenProTree(const QString &src_path, int file_count, QTreeWidget *self)//打开
{
    QDir src_dir(src_path);
    auto name=src_dir.dirName();
    //创建一个根节点
    auto *item=new ProTreeItem(self,name,src_path,TreeItemPro);
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/photo/OIP.jpg"));
    item->setData(0,Qt::ToolTipRole,src_path);
    _root=item;

    RecursiveProTree(src_path,file_count,self,_root,item,nullptr);//递归调用
}

void OpenTreeThread::run()
{
    OpenProTree(_src_path,_file_count,_self);
    if(_bstop)
    {
        auto path=dynamic_cast<ProTreeItem*>(_root)->GetPath();//获取路径

        //树中删除
        int dex=_self->indexOfTopLevelItem(_root);
        delete _self->takeTopLevelItem(dex);

        //删除文件夹
        QDir dir(path);
        dir.removeRecursively();
        return;

    }

    emit SigFinishProgress(_file_count);
}

void OpenTreeThread::RecursiveProTree(const QString &src_path, int file_count, QTreeWidget *self,
                                      QTreeWidgetItem *root, QTreeWidgetItem *parent, QTreeWidgetItem *preitem)
{
    QDir dir(src_path);
    dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);
    QFileInfoList list=dir.entryInfoList();
    for(int i=0;i<list.size();i++)
    {
        if(_bstop)
        {
            return;
        }

        QFileInfo fileInfo=list.at(i);
        bool bisdir=fileInfo.isDir();//判断是否是文件夹
        if(bisdir)
        {
            file_count++;
            emit SigUpdateProgress(file_count);
            auto *item=new ProTreeItem(_root,fileInfo.fileName(),fileInfo.absoluteFilePath(),_root,TreeItemDir);
            item->setData(0,Qt::DisplayRole,fileInfo.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/photo/OIP.jpg"));
            item->setData(0,Qt::ToolTipRole,fileInfo.absoluteFilePath());
            RecursiveProTree(fileInfo.absoluteFilePath(),file_count,self,root,item,preitem);//递归调用
        }
        else
        {
            const QString& suffix=fileInfo.completeSuffix();
            if(suffix!="png"&&suffix!="jpeg"&&suffix!="jpg")
            {
                continue;
            }
            file_count++;
            emit SigUpdateProgress(file_count);

            auto *item=new ProTreeItem(_root,fileInfo.fileName(),fileInfo.absoluteFilePath(),_root,TreeItemPic);
            item->setData(0,Qt::DisplayRole,fileInfo.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/photo/OIP (1).jpg"));
            item->setData(0,Qt::ToolTipRole,fileInfo.absoluteFilePath());

            if(preitem)
            {
                auto* pre_item=dynamic_cast<ProTreeItem*>(preitem);
                pre_item->SetNextItem(item);
            }

            item->SetPreItem(preitem);
            preitem=item;
        }
    }
    emit SigFinishProgress(file_count);
}

void OpenTreeThread::SlotCanceled_open()
{
    this->_bstop=true;
}

