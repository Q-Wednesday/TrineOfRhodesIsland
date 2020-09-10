#ifndef HIDENTRAP_H
#define HIDENTRAP_H
#include"trap.h"
//隐藏陷阱，和地面的长相一样，但是当人靠近时会发射炮弹（最多3次）

class HidenTrap:public Trap{
public:
    HidenTrap(int x,int y,int T,QObject*parent=nullptr);
    ~HidenTrap();
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void launch() override;
private:
     int m_launched;//生成数，不会超过上限
};

#endif // HIDENTRAP_H
