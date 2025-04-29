#include "mainwindow.h"

#include <QApplication>
#include<QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile qss(":/style/style.qss");//打开qss文件 加载样式
    if(qss.open(QFile::ReadOnly))//只读的方式打开
    {
        //qDebug()<<"open qss success";
        QString style=QLatin1String(qss.readAll());
        a.setStyleSheet(style);//设置样式表
    }
    else
    {
        qDebug()<<"open qss filed";
        return 0;
    }
    w.setWindowTitle("电子相册");
    w.setWindowIcon(QIcon(":/photo/test/R.jpg"));
    w.showMaximized();//最大化显示
    //w.show();
    return a.exec();
}
