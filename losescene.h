#ifndef LOSESCENE_H
#define LOSESCENE_H

#include <QWidget>

namespace Ui {
class LoseScene;
}

class LoseScene : public QWidget
{
    Q_OBJECT

public:
    explicit LoseScene(QWidget *parent = nullptr);
    ~LoseScene();
    void setTime(int secs);
private slots:
    void on_pushButton_clicked();
signals:
    void toTitle();
private:
    Ui::LoseScene *ui;
};

#endif // LOSESCENE_H
