#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
#include<QObject>
#include<QImage>
#include"constant.h"
class AnimationManager:public QObject{
    Q_OBJECT
public:
    AnimationManager(QObject* parent=nullptr);
    AnimationManager(QVector<QString> filepath,QVector<int> framesnum,QObject* parent=nullptr);
    ~AnimationManager();
    QImage& get_currentframe();
    void advance();//在角色的advance中调用，将帧后移，播放攻击动画会发射信号
    void set_frame_vector(QVector<int> framecevtor);
    void set_filepath( QVector<QString>filepath);
    animeMode get_mode();
public slots:
    void changeMode(animeMode mode);
signals:
    //处理非循环播放动画的信号
    void attackFinish();
    void dieFinish();
    void skillFinish();
private:
    int m_frame;//播放到哪一帧
    animeMode m_mode;//当前动画模式
    QVector<int> m_framevector;//各种模式帧数
    QVector<QString>m_filepath;//各种模式对应的文件夹
    QImage m_currentframe;//当前帧
};

#endif // ANIMATIONMANAGER_H
