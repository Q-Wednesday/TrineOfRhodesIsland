#ifndef SELECTMAPSCENE_H
#define SELECTMAPSCENE_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPushButton>
#include<QSignalMapper>
#include<QLabel>
#include<QFormLayout>
#include<QGridLayout>
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
    void toTitle();
private slots:
    void on_pushButton_clicked();

private:
    Ui::SelectMapScene *ui;
    QGridLayout* m_layout;
    QVector<QPushButton*>m_buttons;
    QSignalMapper* m_mapper;
    QSignalMapper* m_mapper_edit;
    QVector<QLabel*>m_labels;
    QVector<QPushButton*>m_editbuttons;
};

#endif // SELECTMAPSCENE_H
