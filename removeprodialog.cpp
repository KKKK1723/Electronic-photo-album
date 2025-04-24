#include "removeprodialog.h"
#include "ui_removeprodialog.h"

RemoveProDialog::RemoveProDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveProDialog)
{
    ui->setupUi(this);
}

RemoveProDialog::~RemoveProDialog()
{
    delete ui;
}

bool RemoveProDialog::IsRemove()
{
    return ui->checkBox->isChecked();//是否选择删除
}
