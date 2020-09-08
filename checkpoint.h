#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include"entity.h"
#include"constant.h"
class CheckPoint:public Entity{
    Q_OBJECT
public:
    CheckPoint(int x,int y,bool is_destination,QObject* parent =nullptr);
    ~CheckPoint();
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
    bool is_destination();
signals:
    void achieve(CheckPoint*);
    void achievefinal();
private:
    bool m_destination;
    bool m_checked;
    QImage m_checked_texture;
    QImage m_unchecked_texture;
};

#endif // CHECKPOINT_H
