#include"normalland.h"
#include<QPainter>
#include"constant.h"
NormalLand::NormalLand(QObject*parent):Land(parent){
    setData(detailType,normalLand);
    m_texture=QPixmap(":/texture/normal");
}

NormalLand::~NormalLand(){

}

NormalLand::NormalLand(int width,int height,int x,int y,QObject* parent):Land(width,height,x,y,parent){
    setData(detailType,normalLand);
    m_texture=QPixmap(":/texture/normal");
}



