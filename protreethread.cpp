#include "protreethread.h"
#include<QDir>
#include "protreeitem.h"
#include"const.h"
#include<QDebug>
ProTreeThread::ProTreeThread(const QString & src_path,
                             const QString& dist_path,
                             QTreeWidgetItem* parent_ite,
                            int file_count,QTreeWidget* self,
                             QTreeWidgetItem* root,
                             QObject* parent)
    :QThread(parent),_src_path(src_path),_dist_path(dist_path),
    _parent_item(parent_ite),_self(self),_root(root),_bstop(false)
{


}

ProTreeThread::~ProTreeThread()
{

}

void ProTreeThread::run()
{
    CreateProTree(_src_path,_dist_path,_parent_item,_file_count,_self,_root);
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

void ProTreeThread::CreateProTree(const QString &src_path, const QString &dist_path, QTreeWidgetItem *parent_item,
                                  int &file_count, QTreeWidget *self, QTreeWidgetItem *root, QTreeWidgetItem *preitem)
{
    if(_bstop)//用户点击了取消
    {
        return;
    }

    bool needcopy=true;//是否需要导入
    if(src_path==dist_path)
    {
        needcopy=false;//相同就不需要了
    }

    QDir import_dir(src_path);
    import_dir.setFilter(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);//保留这些
    import_dir.setSorting(QDir::Name);

    QFileInfoList _list=import_dir.entryInfoList();
    for(int i=0;i<_list.size();i++)
    {
        QFileInfo  file_info=_list.at(i);
        if(_bstop)//用户点击了取消
        {
            return;
        }

        if(file_info.isDir())//是文件夹
        {
            file_count++;
           // qDebug()<<"发送更新信号w"<<Qt::endl;
            emit SigUpdateProgress(file_count);

            QDir dir_path(dist_path);
            QString t_path=dir_path.absoluteFilePath(file_info.fileName());
            QDir t_dir(t_path);
            if(!t_dir.exists())//不存在就创建
            {
                bool isok=t_dir.mkpath(t_path);
                if(!isok)
                {
                    continue;
                }
            }

            auto *item=new ProTreeItem(parent_item,file_info.fileName(),t_path,root,TreeItemDir);
            item->setData(0,Qt::DisplayRole,file_info.fileName());
            item->setData(0,Qt::ToolTipRole,t_path);
            item->setData(0,Qt::DecorationRole,QIcon(":/photo/OIP (1).jpg"));
            // if (!parent_item && self) {
            //     self->addTopLevelItem(item);
            // }
            CreateProTree(file_info.absoluteFilePath(),t_path,item,file_count,self,root,preitem);

        }
        else//文件
        {
            if(file_info.completeSuffix()!="png"&&file_info.completeSuffix()!="jpeg"&&file_info.completeSuffix()!="jpg")
            {
                continue;//不是图片
            }

            file_count++;
          //  qDebug()<<"发送更新信号t"<<Qt::endl;
            emit SigUpdateProgress(file_count);

            if(!needcopy)
            {
                continue;
            }

            QDir dir_path(dist_path);
            QString dir_path_t=dir_path.absoluteFilePath(file_info.fileName());
            if(!QFile::copy(file_info.absoluteFilePath(),dir_path_t))
            {
                continue;
            }

            auto *item=new ProTreeItem(parent_item,file_info.fileName(),dir_path_t,root,TreeItemPic);
            item->setData(0,Qt::DisplayRole,file_info.fileName());
            item->setData(0,Qt::ToolTipRole,dir_path_t);
            item->setData(0,Qt::DecorationRole,QIcon(":/photo/OIP (1).jpg"));
            /*f (!parent_item && self) {
                self->addTopLevelItem(item);
            }*/
            //更新链表
            if(preitem)//不为空
            {
                ProTreeItem *pre_item=dynamic_cast<ProTreeItem*>(preitem);//为了使用SetNextItem这个函数
                pre_item->SetNextItem(item);
            }

            item->SetPreItem(preitem);
            preitem=item;
        }
    }

    parent_item->setExpanded(true);//可展开
}

void ProTreeThread::SlotCanceled()
{
   this->_bstop=true;
}



