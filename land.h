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

protected:
    int m_width;
    int m_height;
    QPixmap m_texture;
    /*
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    */
};

#endif // LAND_H
