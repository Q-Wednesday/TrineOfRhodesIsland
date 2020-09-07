#ifndef ENEMYGENERATOR_H
#define ENEMYGENERATOR_H
#include"trap.h"
#include"constant.h"
//怪物生成点，可被破坏
class EnemyGenerator:public Trap{
public:
    EnemyGenerator(int x,int y,EnemyType type,int T,QObject* parent=nullptr);
    ~EnemyGenerator();
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
    EnemyType get_type();
    void launch() override;
private:
    EnemyType m_type;
    int m_generated;//生成数，不会超过上限
};

#endif // ENEMYGENERATOR_H
