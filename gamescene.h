#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QObject>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>
#include <QtGlobal>
#include <QAbstractItemModel>

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject *parent = nullptr);
    void initImage();

    static int index;
public slots:
    void Update();
private:
    QTime t;
    QTimer *ptimer;
    void setNum(int y, int x);
    int calculateBombs(int x, int y);
    void findWhiteCubes(int x, int y);
};

#endif // GAMESCENE_H
