#include"prop.h"
Prop::Prop(QObject* parent):Entity(parent){
    setData(entityType,propType);

}

Prop::Prop(int x,int y,QObject*parent):Prop(parent){
    setPos(x,y);
}




Prop::~Prop(){

}
void Prop::used(Player* player){
    emit deathSignal(this);
}

void Prop::advance(int phase){
    if(!phase)
        return;
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType){
            Player* player=static_cast<Player*>(collision);

            used(player);
        }
    }
}
