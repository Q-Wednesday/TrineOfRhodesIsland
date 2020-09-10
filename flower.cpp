#include"flower.h"
#include<QPainter>
#include"player.h"
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


void Flower::used(Player *player){
    int hp=(player->get_maxhp()>player->get_hp()+2)? (player->get_hp()+5):player->get_maxhp();
    player->add_skill_point(4);
    player->skill();
    emit deathSignal(this);
}
