#ifndef PICANIMATIONWID_H
#define PICANIMATIONWID_H
#include<QWidget>
#include<QTreeWidgetItem>

class PicAnimationWid : public QWidget
{
    Q_OBJECT
public:
    explicit PicAnimationWid(QWidget *parent = nullptr);
    ~PicAnimationWid();
    void SetPixmap(QTreeWidgetItem* item);
    void Start();
    void Stop();

    void SlidNext();
    void Slidpre();

protected:
    virtual void paintEvent(QPaintEvent *event);//重绘




private:
    void UpSelectPixmap(QTreeWidgetItem* item);
    float _factor;
    QTimer* _timer;
    QPixmap _pixmap1;
    QPixmap _pixmap2;
    QTreeWidgetItem* _cur_item;
    QMap<QString,QTreeWidgetItem*>_map_items;
    bool _b_start;

private slots:
    void TimeOut();
signals:
    void SigUpPreList(QTreeWidgetItem*);
    void SigSelectItem(QTreeWidgetItem*);
    void SigStart();
    void SigStop();
    void SigStartMusic();
    void SigStopMusic();

public slots:
    void SlotUpSelectShow(QString path );
    void SlotStartOrStop();
};

#endif // PICANIMATIONWID_H
