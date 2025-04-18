#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget* _protree;//用基类! 降低类与类之间的耦合性 如果这里用protree类型，protree中也用到mainwindow 可能会引发互引用问题


private slots:
    void SlotCreatePro(bool);

};
#endif // MAINWINDOW_H
