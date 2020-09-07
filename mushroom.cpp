#include"mushroom.h"
#include<QPainter>
#include"character.h"
#include<QDebug>
Mushroom::Mushroom(int x,int y,QObject* parent):Prop(x,y,parent){
    setData(detailType,mushRoom);
}

Mushroom::~Mushroom(){

}


QRectF Mushroom::boundingRect() const{
    return QRectF(-42,-38,85,77);
}

QPainterPath Mushroom::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Mushroom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawImage(boundingRect(),QImage(":/texture/mushroom"));
    qDebug()<<"paint mushroom";
}

void Mushroom::advance(int phase){
    if(!phase)
        return;
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType){
            Character* c=static_cast<Character*>(collision);
            c->set_hp(c->get_hp()+3);
            used();
        }
    }
}
