#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QWidget>

namespace Ui {
class EditorTab;
}

class EditorTab : public QWidget
{
    Q_OBJECT

public:
    explicit EditorTab(QWidget *parent = nullptr);
    ~EditorTab();

signals:
    void addNormalLand(int,int);
    void moveScene(int,int);
    void addSpikeLand(int,int,int);
    void saveMap(QString);
    void addWorm1();
    void addWorm2();
    void addCheckPoint();
    void addGenerator(int,int);//第一个参数是种类，第二个是时间
    void addMovingLand(int,int,int);//参数T
    void addMushroom();
    void addSpringLand();
    void addFragileLand(int,int);
    void addWorm3();
    void addFlower();
private slots:
    void on_normalLandButton_clicked();

    void on_moveToRight_clicked();

    void on_saveButton_clicked();


    void on_spikeLandButton_clicked();

    void on_worm1Button_clicked();


    void on_moveToLeft_clicked();

    void on_checkPointButton_clicked();

    void on_worm2Button_clicked();

    void on_worm1GeneratorButton_clicked();

    void on_worm2GeneratorButton_clicked();

    void on_movingLandButton_clicked();

    void on_mushroomButton_clicked();

    void on_springLandButton_clicked();

    void on_fragileButton_clicked();

    void on_worm3Button_clicked();

    void on_flowerButton_clicked();

private:
    Ui::EditorTab *ui;
};

#endif // EDITORTAB_H
