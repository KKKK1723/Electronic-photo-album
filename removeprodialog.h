#ifndef REMOVEPRODIALOG_H
#define REMOVEPRODIALOG_H

#include <QDialog>

namespace Ui {
class RemoveProDialog;
}

class RemoveProDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveProDialog(QWidget *parent = nullptr);
    ~RemoveProDialog();
    bool IsRemove();//是否删除
private:
    Ui::RemoveProDialog *ui;

};

#endif // REMOVEPRODIALOG_H
