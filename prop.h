#ifndef PROP_H
#define PROP_H
#include"entity.h"
#include"constant.h"
#include"player.h"
//道具类
class Prop:public Entity{
public:
     Prop(QObject* parent=nullptr);
     Prop(int x,int y,QObject*parent=nullptr);
     ~Prop();

     void advance(int phase);
protected:
     virtual void used(Player* player);
};

#endif // PROP_H
