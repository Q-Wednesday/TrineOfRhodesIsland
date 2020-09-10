#ifndef ADVENTURESCENE_H
#define ADVENTURESCENE_H

#include <QWidget>

namespace Ui {
class AdventureScene;
}

class AdventureScene : public QWidget
{
    Q_OBJECT

public:
    explicit AdventureScene(QWidget *parent = nullptr);
    ~AdventureScene();

private slots:
    void on_level1Button_clicked();
    void on_level2Button_clicked();

signals:
    void toLevel(QString);
private:
    Ui::AdventureScene *ui;
};

#endif // ADVENTURESCENE_H
