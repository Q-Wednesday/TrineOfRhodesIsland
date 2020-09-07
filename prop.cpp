#include"prop.h"
Prop::Prop(QObject* parent):Entity(parent){
    setData(entityType,propType);

}

Prop::Prop(int x,int y,QObject*parent):Prop(parent){
    setPos(x,y);
}




Prop::~Prop(){

}
void Prop::used(){
    emit deathSignal(this);
}
