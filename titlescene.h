#ifndef TITLESCENE_H
#define TITLESCENE_H

#include <QWidget>

namespace Ui {
class TitleScene;
}

class TitleScene : public QWidget
{
    Q_OBJECT

public:
    explicit TitleScene(QWidget *parent = nullptr);
    ~TitleScene();
signals:
    void toDesign();
    void toSelect();
    void toAdventure();
private slots:
    void on_designButton_clicked();

    void on_playMyButton_clicked();

    void on_quitButton_clicked();

    void on_adventureButton_clicked();

private:
    Ui::TitleScene *ui;
};

#endif // TITLESCENE_H
