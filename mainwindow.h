#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include"titlescene.h"
#include"editorscene.h"
#include"selectmapscene.h"
#include"winscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //void setCentralWidget(QWidget* widget);
public slots:
    void toEditorScene();
    void toReEditScene(QString filename);//对已经存在的地图进行编辑
    void toMyScene(QString filename);
    void toSelectScene();
    void toTitle();
    void toWinScene();
private:
    Ui::MainWindow *ui;
    TitleScene* m_title;
    QTimer* m_timer;
    SelectMapScene* m_selectscene;
    GameController* m_controller;
    EditorScene* m_editorscene;
    WinScene* m_winscene;
};
#endif // MAINWINDOW_H
