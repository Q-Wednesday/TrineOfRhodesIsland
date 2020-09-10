#ifndef TRAP_H
#define TRAP_H
#include"land.h"
#include"airwall.h"
//带有触发机制的陷阱类
class Trap:public Land{
    Q_OBJECT
public:
    Trap(int width,int height,int x,int y,int T,QObject*parent=nullptr);
    ~Trap();
    virtual void launch()=0;//陷阱发动
    int get_T();
    void advance(int phase)override;
protected:
    AirWall* m_range;//表示触发的范围
    int m_tick;
    int m_T;//周期
};

#endif // TRAP_H
