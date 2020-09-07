#ifndef MOVINGLAND_H
#define MOVINGLAND_H
#include"land.h"
#include"airwall.h"
class MarkPoint:public AirWall{
public:
    MarkPoint(QGraphicsItem* parent=nullptr):AirWall(parent),m_candrag(false){ }
    ~MarkPoint(){};
    void set_can_drag(bool on=true);
private:
        bool m_candrag;
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class MovingLand:public Land{
    Q_OBJECT
public:
    MovingLand(int width,int height,int x,int y,int T,QObject*parent=nullptr);//编辑时的够造
    MovingLand(int width,int height,int T,QPointF start,QPointF end,QObject*parent=nullptr);
    ~MovingLand();
    void advance(int phase)override;
    QVector<QPointF> get_path();
    QVector<AirWall*> get_point();
    int get_T();
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
private:

    QPointF m_startpoint;
    QPointF m_endpoint;
    MarkPoint* m_start;
    MarkPoint* m_end;
    int m_T;

};

#endif // MOVINGLAND_H
