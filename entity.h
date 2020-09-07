#ifndef ENTITY_H
#define ENTITY_H
#include<QGraphicsItem>
class Entity:public QObject,public QGraphicsItem{
    Q_OBJECT;
public:
    Entity(QObject* parent=nullptr);
    ~Entity();
    void setAdvanceEnanbled(bool on);
    void set_speed(int speed);
signals:
    void deathSignal(Entity*);
    void addEntity(Entity*);
public slots:
    //获取与改变血量
    void set_hp(int hp);
    int get_hp();
    int get_maxhp();
    //获取与改变重量
    void set_weight(int weight);
    int get_weight();
    void set_can_drag(bool on=true);
protected:
    bool m_candrag;
    int m_hp;//血量
    int m_maxhp;
    int m_weight;//重量
    qreal m_speedx;//横向速度
    qreal m_speedy;//纵向速度
    qreal m_ay;//横向加速度
    qreal m_ax;//纵向加速度
     bool m_enabled;//是否在场景中启用
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // ENTITY_H
