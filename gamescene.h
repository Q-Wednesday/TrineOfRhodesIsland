#ifndef GAMESCENE_H
#define GAMESCENE_H
#include<QObject>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QPushButton>
#include<QLabel>
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
    void loadMap(QString filename);//用于编辑模式的接口
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    void toTitle();
    void toWinScene();
public slots:
    //编辑模式添加元素
    void addNormalLand(int width,int height);
    void addWorm1();
    void addWorm2();
    void addWorm3(); 
    void addSpikeLand(int width,int height,int attack);
    void addEntity(Entity* entity);
    void addCheckPoint();
    void addDestination();
    void addGenerator(int type,int T);
    void addMovingLand(int width,int height,int T);
    void addMushroom();
    void addSpringLand();
    void addFragileLand(int width,int height);
    void addFlower();
    void addHintLand(QString hint);
    //其他功能
    void autoSave(Entity* checkpoint);//保存点
    void changeSceneRect(int dx,int dy);//移动场景
    void saveScene(QString filename);//保存场景
    void advance();//场景更新（用于移动）
    void deleteDeadOne(Entity* dead);//去除不需要的物体
    void showHint(QString hint);//显示提示
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
    QLabel* m_hintlabel;//提示词用
    void setUpUI();//放置UI
    void moveScene();//缓慢地移动场景和UI
    DeadZone* m_deadzone;

    CheckPoint* m_lastpoint;
};

#endif // GAMESCENE_H
