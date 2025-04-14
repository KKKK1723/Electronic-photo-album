#include "protree.h"
#include "ui_protree.h"

ProTree::ProTree(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProTree)
{
    ui->setupUi(this);
    this->setMinimumWidth(378);//固定宽
    this->setMaximumWidth(378);
}

ProTree::~ProTree()
{
    delete ui;
}

void ProTree::AddProTree(const QString name, const QString path)
{
    ui->treeWidget->AddProTree(name,path);
}
