#ifndef GAMESCENE_H
#define GAMESCENE_H
#include<QObject>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QPushButton>
#include"gamecontroller.h"
#include"entity.h"
#include"allentities.h"
class GameScene:public QObject{
    Q_OBJECT
public:
    GameScene(QObject* parent=nullptr);
    ~GameScene();
    GameScene(QString filename,QObject* parent=nullptr);
    QGraphicsView* view();
    QGraphicsScene* scene();
    QRect get_scene_rect() const;

    CheckPoint* get_last_point();
    void changeSceneRectNow(int dx,int dy);//打断当前屏幕移动，立即移动
    void reset();
    void reset(QString filename);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    void toTitle();
public slots:
    void addNormalLand(int width,int height);
    void addWorm1();
    void addWorm2();
    void changeSceneRect(int dx,int dy);
    void saveScene(QString filename);
    void advance();
    void deleteDeadOne(Entity* dead);
    void addSpikeLand(int width,int height,int attack);
    void addEntity(Entity* entity);
    void addCheckPoint();
    void autoSave(Entity* checkpoint);
    void addGenerator(int type,int T);
    void addMovingLand(int width,int height,int T);
    void addMushroom();
private:
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
    QRect m_sceneRect;
    //friend GameController;
    bool m_can_edit;
    int m_movex;
    int m_movey;
    int m_movespeed;
    bool m_moving;

    //UI控件
    QPushButton* m_titlebutton;
    void setUpUI();//放置UI
    void moveScene();//缓慢地移动场景和UI
    DeadZone* m_deadzone;

    CheckPoint* m_lastpoint;
};

#endif // GAMESCENE_H
