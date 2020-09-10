#ifndef FRAGILELAND_H
#define FRAGILELAND_H
#include"land.h"
class FragileLand:public Land{
public:
    FragileLand(int width,int height,int x,int y,QObject*parent=nullptr);
    ~FragileLand();
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
private:
    QPixmap m_broken_texture;
};

#endif // FRAGILELAND_H
