#ifndef TITLESCENE_H
#define TITLESCENE_H

#include <QWidget>
#include"setvolumedialog.h"
namespace Ui {
class TitleScene;
}

class TitleScene : public QWidget
{
    Q_OBJECT

public:
    explicit TitleScene(QWidget *parent = nullptr);
    ~TitleScene();
    SetVolumeDialog* get_dialog();
signals:
    void toDesign();
    void toSelect();
    void toAdventure();
private slots:
    void on_designButton_clicked();

    void on_playMyButton_clicked();

    void on_quitButton_clicked();

    void on_adventureButton_clicked();

    void on_voiceButton_clicked();

private:
    Ui::TitleScene *ui;
    SetVolumeDialog* m_volumedialog;
};

#endif // TITLESCENE_H
