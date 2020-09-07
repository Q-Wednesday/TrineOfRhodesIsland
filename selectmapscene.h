#ifndef SELECTMAPSCENE_H
#define SELECTMAPSCENE_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPushButton>
#include<QSignalMapper>
#include<QLabel>
namespace Ui {
class SelectMapScene;
}

class SelectMapScene : public QWidget
{
    Q_OBJECT

public:
    explicit SelectMapScene(QWidget *parent = nullptr);
    ~SelectMapScene();
    void reset();
signals:
    void openMap(QString filename);
    void editMap(QString filename);
private:
    Ui::SelectMapScene *ui;
    QVBoxLayout* m_layout;
    QVector<QPushButton*>m_buttons;
    QSignalMapper* m_mapper;
    QSignalMapper* m_mapper_edit;
    QVector<QLabel*>m_labels;
    QVector<QPushButton*>m_editbuttons;
};

#endif // SELECTMAPSCENE_H
