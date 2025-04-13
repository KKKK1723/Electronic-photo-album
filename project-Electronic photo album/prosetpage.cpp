#include "prosetpage.h"
#include "ui_prosetpage.h"
#include<QLineEdit>
#include<QDir>
ProSetPage::ProSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProSetPage)
{
    ui->setupUi(this);
    //注册域 如果没输入 下一步就是灰色的
    registerField("proPath",ui->lineEdit_2);
    registerField("proName*",ui->lineEdit);
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

bool ProSetPage::isComplete() const
{
    if(ui->lineEdit->text()==""||ui->lineEdit_2->text()==""){
        return false;//必须要输入
    }

    QDir dir(ui->lineEdit_2->text());//获取文本
    if(!dir.exists()){
        ui->tips->setText("路径不存在！");
        return false;
    }


    //判断路径
    QString absFilePath=dir.absoluteFilePath(ui->lineEdit->text());//加上完整路径
    QDir dist_dir(absFilePath);
    if(dist_dir.exists()){
        ui->tips->setText("项目已存在！请更换路径或名字");
        return false;
    }

    ui->tips->setText("");
    return QWizardPage::isComplete();//如果重写了基类的虚函数 后续还想再用其原本的功能 需要返回
}
