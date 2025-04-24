#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>

namespace Ui {
class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT

public:
    explicit Wizard(QWidget *parent = nullptr);//构造函数
    ~Wizard();

protected:
    void done(int result) override;//一般子类继承基类的函数时用protected

private:
    Ui::Wizard *ui;

signals:
    void SigProSettings(const QString name,const QString  path);
};

#endif // WIZARD_H
