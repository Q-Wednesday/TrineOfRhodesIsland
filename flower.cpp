#include"flower.h"
#include<QPainter>
#include"character.h"
Flower::Flower(int x,int y,QObject*parent):Prop(x,y,parent){
    setData(detailType,flower);
}

Flower::~Flower(){

}

QRectF Flower::boundingRect() const{
    return QRectF(-38,-38,77,77);
}

QPainterPath Flower::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Flower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawImage(boundingRect(),QImage(":/texture/flower"));
}

void Flower::advance(int phase){
    if(!phase)
        return;
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType){
            Character* c=static_cast<Character*>(collision);
            c->set_hp(c->get_hp()+2);
            c->add_skill_point(3);
            c->skill();

            used();
        }
    }
}
