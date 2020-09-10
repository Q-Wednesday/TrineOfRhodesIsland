#ifndef DEADZONE_H
#define DEADZONE_H
#include"airwall.h"
//死亡空间，碰到这个空间之后玩家（仅玩家！）会被判定为死亡
//不需要被写进文件中，每个场景被创建时需要自动创建
class DeadZone:public AirWall{

public:
    DeadZone(int width,int height,int x,int y,QObject*parent=nullptr);
    ~DeadZone();

    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
};

#endif // DEADZONE_H
