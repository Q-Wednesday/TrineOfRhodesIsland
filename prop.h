#ifndef PROP_H
#define PROP_H
#include"entity.h"
#include"constant.h"
//道具类
class Prop:public Entity{
public:
     Prop(QObject* parent=nullptr);
     Prop(int x,int y,QObject*parent=nullptr);
     ~Prop();
     void used();

};

#endif // PROP_H
