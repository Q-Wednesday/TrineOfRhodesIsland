#ifndef MAPREADER_H
#define MAPREADER_H
#include<QObject>
#include<entity.h>
#include<QVector>
class MapReader:public QObject{
public:
    MapReader();
    ~MapReader();


    static QVector<Entity*> readMap(QString filename);
    static void writeMap(QString filename,QList<QGraphicsItem*> list);

};

#endif // MAPREADER_H
