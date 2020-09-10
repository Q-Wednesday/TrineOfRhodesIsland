#ifndef ENTITY_H
#define ENTITY_H
#include<QGraphicsItem>
class Entity:public QObject,public QGraphicsItem{
    Q_OBJECT;
public:
    Entity(QObject* parent=nullptr);
    ~Entity();
    //
    void setAdvanceEnanbled(bool on);
    void set_speed(int speed);
    //获取与改变血量
    void set_hp(int hp);
    int get_hp();
    int get_maxhp();
    //在编辑模式下调用使物体可以被拖动
    void set_can_drag(bool on=true);
signals:
    void deathSignal(Entity*);
    void addEntity(Entity*);

protected:
    bool m_candrag;//能否被拖动，标志了是否在编辑模式
    bool m_enabled;//是否在场景中启用

    int m_hp;//血量
    int m_maxhp;//最大血量
    qreal m_speedx;//横向速度
    qreal m_speedy;//纵向速度
    qreal m_ay;//横向加速度
    qreal m_ax;//纵向加速度


     //实现拖动事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // ENTITY_H
