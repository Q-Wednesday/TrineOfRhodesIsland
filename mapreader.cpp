#include"mapreader.h"
#include<QDir>
#include<QFile>
#include<QJsonArray>
#include<QDebug>
#include<QJsonParseError>
#include<QJsonDocument>
#include<QJsonObject>
#include"allentities.h"
#include<QDebug>
#include"constant.h"
MapReader::MapReader(){

}

MapReader::~MapReader(){

}


QVector<Entity*> MapReader::readMap(QString filename){
    QVector<Entity*> entity_vector;

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"文件打开失败";
        return entity_vector;
    }
    qDebug()<<"文件打开成功";
    QJsonParseError jsonParserError;
    QJsonDocument jsonDocument=QJsonDocument::fromJson(file.readAll(),&jsonParserError);

    if(jsonDocument.isNull()|| !jsonParserError.error==QJsonParseError::NoError){
        return entity_vector;
    }
    qDebug()<<"文件解析成功";
    QJsonArray entityArray=jsonDocument.array();
    for(int i=0;i<entityArray.size();i++){
        QJsonObject entityInfo=entityArray[i].toObject();
        if(entityInfo.value("entityType")==2){

            switch (entityInfo.value("typeNum").toInt()) {
            case 0:
            {
                NormalLand* normalland=new NormalLand(entityInfo.value("width").toInt(),
                                                      entityInfo.value("height").toInt(),
                                                      entityInfo.value("x").toInt(),
                                                      entityInfo.value("y").toInt());
                entity_vector.append(normalland);
                break;
            }
            case 1:
            {
                SpikeLand* spikeland=new SpikeLand(entityInfo.value("width").toInt(),
                                                   entityInfo.value("height").toInt(),
                                                   entityInfo.value("x").toInt(),
                                                   entityInfo.value("y").toInt(),
                                                   entityInfo.value("attack").toInt());
                entity_vector.append(spikeland);
                break;
            }
            case 2:
            {
                MovingLand*movingland=new MovingLand(entityInfo.value("width").toInt(),
                                                     entityInfo.value("height").toInt(),
                                                     entityInfo.value("T").toInt(),
                                                     QPointF(entityInfo.value("s_x").toInt(),
                                                             entityInfo.value("s_y").toInt()),
                                                     QPointF(entityInfo.value("e_x").toInt(),
                                                             entityInfo.value("e_y").toInt()));
                entity_vector.append(movingland);
                break;
            }
            case 3:{
                SpringLand* springland=new SpringLand(entityInfo.value("x").toInt(),
                                                      entityInfo.value("y").toInt());
                entity_vector.append(springland);
                break;
            }
            case 4:{
                FragileLand* fragileland=new FragileLand(entityInfo.value("width").toInt(),
                                                         entityInfo.value("height").toInt(),
                                                         entityInfo.value("x").toInt(),
                                                         entityInfo.value("y").toInt());
                entity_vector.append(fragileland);
                break;
            }
            case 5:{
                HintLand* hintland=new HintLand(entityInfo.value("width").toInt(),
                                                entityInfo.value("height").toInt(),
                                                entityInfo.value("x").toInt(),
                                                entityInfo.value("y").toInt(),
                                                entityInfo.value("hint").toString());
                entity_vector.append(hintland);
                break;
            }
            }
        }
        else if(entityInfo.value("entityType")==1){
            switch (entityInfo.value("typeNum").toInt()) {
            case 0:{
                Worm1* worm1=new Worm1(entityInfo.value("x").toInt(),
                                       entityInfo.value("y").toInt());
                entity_vector.append(worm1);
                break;
            }
            case 1:{
                Worm2* worm2=new Worm2(entityInfo.value("x").toInt(),
                                       entityInfo.value("y").toInt());
                entity_vector.append(worm2);
                break;
            }
            case 2:{
                Worm3* worm3=new Worm3(entityInfo.value("x").toInt(),
                                       entityInfo.value("y").toInt());
                entity_vector.append(worm3);
                break;
            }
            }
        }
        else if(entityInfo.value("entityType")==4){
            CheckPoint* checkpoint=new CheckPoint(entityInfo.value("x").toInt(),
                                                  entityInfo.value("y").toInt(),
                                                  entityInfo.value("destination").toBool());
            entity_vector.append(checkpoint);

        }
        else if(entityInfo.value("entityType")==5){
            switch (entityInfo.value("typeNum").toInt()) {
            case 0:{

                EnemyGenerator* generator=new EnemyGenerator(entityInfo.value("x").toInt(),
                                                             entityInfo.value("y").toInt(),
                                                             (EnemyType)entityInfo.value("enemyType").toInt(),
                                                             entityInfo.value("T").toInt());
                entity_vector.append(generator);
                break;
            }
            }
        }
        else if(entityInfo.value("entityType")==6){
            switch(entityInfo.value("typeNum").toInt()){
            case 0:{
                Mushroom* mushroom=new Mushroom(entityInfo.value("x").toInt(),
                                                entityInfo.value("y").toInt());
                entity_vector.append(mushroom);
                break;
            }
            case 1:{
                Flower* aflower=new Flower(entityInfo.value("x").toInt(),
                                           entityInfo.value("y").toInt());
                entity_vector.append(aflower);
                break;
            }

            }
        }
    }
    file.close();
    return entity_vector;
}

void MapReader::writeMap(QString filename,QList<QGraphicsItem*> list){
    QDir dir;
    QString path=dir.currentPath()+"/maps";
    if(!dir.exists(path)){
        dir.mkpath(path);
    }
    QFile file(path+"/"+filename);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug()<<"文件打开失败";
        return;
    }
    //qDebug()<<"文件打开成功";
    QJsonArray entityArray;
    //qDebug()<<list.size()<<"个物体";
    for(auto i:list){
        qDebug()<<i->data(entityType);
        QJsonObject entity;
        if(i->data(entityType)==landType){
            entity.insert("entityType",2);
            Land* land=static_cast<Land*>(i);
            entity.insert("width",land->get_width());
            entity.insert("height",land->get_height());
            entity.insert("x",land->pos().x());
            entity.insert("y",land->pos().y());
            switch (i->data(detailType).toInt()) {
            case normalLand:
            {
                entity.insert("typeNum",0);
                //NormalLand* normal_land=static_cast<NormalLand*>(i);
                break;
            }
            case spikeLand:
            {
                entity.insert("typeNum",1);
                SpikeLand* spike_land=static_cast<SpikeLand*>(i);
                entity.insert("attack",spike_land->get_attack());
                break;
            }
            case movingLand:
            {
                entity.insert("typeNum",2);
                MovingLand* movingland=static_cast<MovingLand*>(i);
                QVector<QPointF> poslist=movingland->get_path();
                entity.insert("T",movingland->get_T());
                entity.insert("s_x",poslist[0].x());
                entity.insert("s_y",poslist[0].y());
                entity.insert("e_x",poslist[1].x());
                entity.insert("e_y",poslist[1].y());
                break;
            }
            case springLand:{
                entity.insert("typeNum",3);
                break;
            }
            case fragileLand:{
                entity.insert("typeNum",4);
                break;
            }
            case hintLand:{
                entity.insert("typeNum",5);
                HintLand* land=static_cast<HintLand*>(i);
                entity.insert("hint",land->get_hint());
                break;
            }
            }
        }
        else if (i->data(entityType)==enemyType) {
            entity.insert("entityType",1);
            Enemy*enemy=static_cast<Enemy*>(i);
            entity.insert("x",enemy->pos().x());
            entity.insert("y",enemy->pos().y());
            switch (i->data(detailType).toInt()) {
            case worm1:
                entity.insert("typeNum",0);
                break;
            case worm2:
                entity.insert("typeNum",1);
                break;
            case worm3:
                entity.insert("typeNum",2);
                break;
            }
        }
        else if (i->data(entityType)==checkPoint) {
            //qDebug()<<"write";
            entity.insert("entityType",4);
            entity.insert("x",i->pos().x());
            entity.insert("y",i->pos().y());
            CheckPoint* point=static_cast<CheckPoint*>(i);
            entity.insert("destination",point->is_destination());
            qDebug()<<entity.keys();

        }
        else if(i->data(entityType)==trapType){
            entity.insert("entityType",5);
            Trap* trap=static_cast<Trap*>(i);
            entity.insert("x",trap->pos().x());
            entity.insert("y",trap->pos().y());
            entity.insert("T",trap->get_T());
            switch (i->data(detailType).toInt()) {
             case enemyGenerator:
                entity.insert("typeNum",0);
                EnemyGenerator* generator=static_cast<EnemyGenerator*>(trap);
                entity.insert("enemyType",generator->get_type());
                break;
            }
        }
        else if(i->data(entityType)==propType){
            entity.insert("entityType",6);
            entity.insert("x",i->pos().x());
            entity.insert("y",i->pos().y());
            switch (i->data(detailType).toInt()) {
            case mushRoom:
                entity.insert("typeNum",0);
                break;
            case flower:
                entity.insert("typeNum",1);
            }
        }
        else{
            continue;
        }
        entityArray.append(entity);
    }
    QJsonDocument jsonDoc;
    jsonDoc.setArray(entityArray);
    file.write(jsonDoc.toJson());

    file.close();

}
