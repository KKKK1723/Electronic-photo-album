#ifndef SLIDSHOWDLG_H
#define SLIDSHOWDLG_H

#include <QDialog>
#include<QTreeWidgetItem>
namespace Ui {
class SlidShowDlg;
}

class SlidShowDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SlidShowDlg(QWidget *parent,QTreeWidgetItem* first_item,
QTreeWidgetItem* last_item);
    ~SlidShowDlg();

private slots:
    void on_closeBtn_clicked();
    void SlotSlidNext();
    void SlotSlidpre();


private:
    Ui::SlidShowDlg *ui;
    QTreeWidgetItem* _first_item;
    QTreeWidgetItem* _last_item;
};

#endif // SLIDSHOWDLG_H
