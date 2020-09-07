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
private:
    Ui::SelectMapScene *ui;
    QVBoxLayout* m_layout;
    QVector<QPushButton*>m_buttons;
    QSignalMapper* m_mapper;
    QVector<QLabel*>m_labels;
};

#endif // SELECTMAPSCENE_H
