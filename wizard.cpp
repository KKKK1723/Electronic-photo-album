#include "wizard.h"
#include "ui_wizard.h"

Wizard::Wizard(QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::Wizard)
{
    ui->setupUi(this);
}

Wizard::~Wizard()
{
    delete ui;
}

//实现完成按钮
void Wizard::done(int result)
{
    if(result==QDialog::Rejected){//如果结果是拒绝
        return QWizard::done(result);
    }

    QString name,path;
    ui->wizardPage1->GetProSettings(name,path);
    emit SigProSettings(name,path);//发出信号
    QWizard::done(result);//如果重写了基类的虚函数
    //后续还想再用其原本的功能 需要再次调用
}
