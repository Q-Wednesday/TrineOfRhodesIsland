#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include"titlescene.h"
#include"editorscene.h"
#include"selectmapscene.h"
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
    void toMyScene(QString filename);
    void toSelectScene();
    void toTitle();
private:
    Ui::MainWindow *ui;
    TitleScene* m_title;
    QTimer* m_timer;
    SelectMapScene* m_selectscene;
    GameController* m_controller;
    EditorScene* m_editorscene;

};
#endif // MAINWINDOW_H
