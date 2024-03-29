#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include"titlescene.h"
#include"editorscene.h"
#include"selectmapscene.h"
#include"winscene.h"
#include"loadingscene.h"
#include"losescene.h"
#include"adventurescene.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void pause();//断开游玩场景的更新
    void resume();//连接游玩场景
    //void setCentralWidget(QWidget* widget);
public slots:
    void toEditorScene();
    void toReEditScene(QString filename);//对已经存在的地图进行编辑
    void toMyScene(QString filename);
    void toSelectScene();
    void toTitle();
    void toWinScene(int score,int secs);
    void toLoseScene(int secs);
    void toNextScene();//接受加载完成的信号，进入下一个场景
    void toAdventureScene();
    void setVolume(int v);

private:
    Ui::MainWindow *ui;
    TitleScene* m_title;
    QTimer* m_timer;
    SelectMapScene* m_selectscene;
    GameController* m_controller;
    EditorScene* m_editorscene;
    WinScene* m_winscene;
    LoseScene* m_losescene;
    LoadingScene* m_loadingscene;
    AdventureScene* m_adventurescene;
    QMediaPlayer* m_player;
    QMediaPlaylist* m_bgm_list;

    QWidget* m_next_scene;
};
#endif // MAINWINDOW_H
