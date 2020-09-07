#include"trap.h"
#include"constant.h"
//T是按秒来算的，但是一秒有33帧
Trap::Trap(int width,int height,int x,int y,int T,QObject*parent):
    Land(width,height,x,y,parent),m_T(T*33),m_tick(0){
    setData(entityType,trapType);
}

Trap::~Trap(){

}

int Trap::get_T(){
    return  m_T/33;
}

