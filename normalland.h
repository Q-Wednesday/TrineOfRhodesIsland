#ifndef NORMALLAND_H
#define NORMALLAND_H
#include"land.h"
class NormalLand:public Land{
public:
    NormalLand(QObject* parent=nullptr);
    NormalLand(int width,int height,int x,int y,QObject* parent=nullptr);
    ~NormalLand();

};

#endif // NORMALLAND_H
