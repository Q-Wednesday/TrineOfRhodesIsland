#ifndef EDITORSCENE_H
#define EDITORSCENE_H
#include<QDockWidget>
#include <QMainWindow>
#include"editortab.h"
#include"gamescene.h"
namespace Ui {
class EditorScene;
}

class EditorScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorScene(QWidget *parent = nullptr);
    ~EditorScene();
    GameScene* get_scene();
    void reset();
    void loadMap(QString filename);
public slots:
    void showTab();
    void toPlay();
signals:
    void toTitle();
    void startPlay(QString);

private:
    Ui::EditorScene *ui;
    GameScene* m_gamescene;//gamescene要不要成为孩子？因为可能要即开即玩
    EditorTab* m_editortab;
    QDockWidget* m_dock;
};

#endif // EDITORSCENE_H
