#ifndef LAND_H
#define LAND_H
#include"entity.h"
//落脚点，包含被动触发的陷阱
class Land:public Entity{
    Q_OBJECT
public:
    Land(QObject* parent=nullptr);
    Land(int width,int height,int x,int y,QObject* parent=nullptr);
    ~Land();
    int get_height();
    int get_width();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
protected:
    int m_width;
    int m_height;
    QPixmap m_texture;

};

#endif // LAND_H
