#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include<QObject>
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
public slots:
    void advance();
    void nextCharacter();
    void preCharacter();
    void resetPlayer(Entity*);
private:
   GameScene* m_gamescene;
   void dealKeyPress(QKeyEvent* event);
   void dealKeyRelease(QKeyEvent* event);
   Character* m_player;
   Exusiai* m_exusiai;
   Silver* m_silver;
   Sheep* m_sheep;
   QVector<Character*>m_characters;
};

#endif // GAMECONTROLLER_H
