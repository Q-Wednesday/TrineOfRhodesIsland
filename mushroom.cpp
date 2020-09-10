#include"mushroom.h"
#include<QPainter>

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
    //qDebug()<<"paint mushroom";
}

void Mushroom::used(Player *player){
    int hp=(player->get_maxhp()>player->get_hp()+5)? (player->get_hp()+5):player->get_maxhp();
    player->set_hp(hp);
    emit deathSignal(this);
}
