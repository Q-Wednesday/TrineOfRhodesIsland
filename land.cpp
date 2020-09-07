#include"land.h"
#include"constant.h"

#include<QDebug>


Land::Land(QObject* parent):Entity(parent),
m_height(100),m_width(100){
    setData(entityType,landType);

}

Land::~Land(){

}

Land::Land(int width,int height,int x,int y,QObject* parent):Entity(parent),
m_height(height),
m_width(width){
    setPos(x,y);
    setData(entityType,landType);
    setAcceptDrops(true);
}

int Land::get_height(){
    return m_height;
}



int Land::get_width(){
    return m_width;
}
/*
void Land::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if(!m_candrag)
        return;

    setCursor(Qt::ClosedHandCursor);
}

void Land::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(!m_candrag)
        return;
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }


    setPos(event->scenePos());
}
void Land::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(!m_candrag)
        return;
    setCursor(Qt::OpenHandCursor);
}
*/
