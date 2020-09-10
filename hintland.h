#ifndef HINTLAND_H
#define HINTLAND_H
#include"Land.h"
//提示地板，站上去的时候会显示提示
class HintLand:public Land{
    Q_OBJECT
public:
    HintLand(int width,int height,int x,int y,QString hint,QObject*parent=nullptr);
    ~HintLand();
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
    QString get_hint();
signals:
    void showHint(QString);
private:
    QString m_hint;
    bool m_showing;//正在显示
};

#endif // HINTLAND_H
