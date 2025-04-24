#include "prosetpage.h"
#include "ui_prosetpage.h"
#include<QLineEdit>
#include<QDir>
#include<QFileDialog>
ProSetPage::ProSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProSetPage)
{
    ui->setupUi(this);
    //注册域 如果*字段没输入 下一步就是灰色的
    registerField("proName*",ui->lineEdit);//*是必填字段
    registerField("proPath",ui->lineEdit_2);

    connect(ui->lineEdit,&QLineEdit::textEdited,this,&ProSetPage::completeChanged);//触发iscomplete函数
    connect(ui->lineEdit_2,&QLineEdit::textEdited,this,&ProSetPage::completeChanged);

    QString curPath=QDir::currentPath();
    ui->lineEdit_2->setText(curPath);//初始的默认路径为当前路径
    //设置光标
    ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().size());
    //只要有输入 就能直接清除
    ui->lineEdit_2->setClearButtonEnabled(true);
    ui->lineEdit->setClearButtonEnabled(true);

}

ProSetPage::~ProSetPage()
{
    delete ui;
}

void ProSetPage::GetProSettings(QString &name, QString &path)//低耦合 用函数单独封装name和path 然后让wizard中的name path接收
{
    name=ui->lineEdit->text();
    path=ui->lineEdit_2->text();
}

//实现强制用户输入正确路径
bool ProSetPage::isComplete() const
{
    if(ui->lineEdit->text()==""||ui->lineEdit_2->text()==""){
        return false;//必须要输入
    }

    QDir dir(ui->lineEdit_2->text());//将文本当成路径 判断此路径是否存在
    if(!dir.exists()){
        ui->tips->setText("路径不存在！");
        return false;
    }


    //判断路径
    QString absFilePath=dir.absoluteFilePath(ui->lineEdit->text());//将第一个text也拼接上来形成完整路径
    QDir dist_dir(absFilePath);
    if(dist_dir.exists()){
        ui->tips->setText("项目已存在！请更换路径或名字");
        return false;
    }

    ui->tips->setText("");//啥也不显示
    return QWizardPage::isComplete();//如果重写了基类的虚函数 后续还想再用其原本的功能 需要返回
}

//浏览按钮
void ProSetPage::on_pushButton_clicked()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);//设置为打开目录 不是文件啥的
    file_dialog.setWindowTitle(tr("选中存放的文件夹"));

    //默认打开路径
    QDir path=QDir::currentPath();
    file_dialog.setDirectory(path);//打开当前的文件
    file_dialog.setViewMode(QFileDialog::Detail);//以详细的信息方式显示

    QStringList list;//存放用户选中的
    if(file_dialog.exec()){
        list=file_dialog.selectedFiles();//用户选中的
    }

    if(list.length()<=0)
    {
        return;
    }

    QString apath=list.at(0);//第一个
    ui->lineEdit_2->setText(apath);
}

