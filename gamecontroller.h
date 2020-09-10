#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include<QObject>
#include<QTime>
#include"gamescene.h"
#include"silver.h"
#include"exusiai.h"
#include"normalland.h"
#include"sheep.h"
class GameScene;
class GameController:public QObject{
Q_OBJECT
public:
    GameController(QObject*parent=nullptr);
    GameController(QString mapName,QObject*parent=nullptr);
    ~GameController();
    GameScene* get_scene();
    void reset(QString filename);
    void set_character();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    void toWinScene(int,int);//通关分数与时间,单位秒
    void changeScore(int);//分数改变
    void toLoseScene(int);//
public slots:
    void advance();
    void nextCharacter();
    void preCharacter();
    void resetPlayer(Entity*);
    void winGame();
    void achieveCheckPoint();
private:
   GameScene* m_gamescene;
   void dealKeyPress(QKeyEvent* event);
   void dealKeyRelease(QKeyEvent* event);
   Player* m_player;
   Exusiai* m_exusiai;
   Silver* m_silver;
   Sheep* m_sheep;
   QVector<Player*>m_characters;
   QTime m_start_time;
   int m_score;//分数，扣分制，死亡时扣分，扣到0分就失败
};

#endif // GAMECONTROLLER_H
