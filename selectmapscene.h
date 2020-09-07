#ifndef SELECTMAPSCENE_H
#define SELECTMAPSCENE_H

#include <QWidget>

namespace Ui {
class SelectMapScene;
}

class SelectMapScene : public QWidget
{
    Q_OBJECT

public:
    explicit SelectMapScene(QWidget *parent = nullptr);
    ~SelectMapScene();
signals:
    void openMap(QString filename);
private:
    Ui::SelectMapScene *ui;
};

#endif // SELECTMAPSCENE_H
