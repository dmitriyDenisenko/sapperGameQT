#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QObject>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>
#include <QtGlobal>
#include <QAbstractItemModel>
#include <item.h>

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject *parent = nullptr, int row = 9, int column = 9, int bomb = 9);
    void initImage();

    static int index;
public slots:
    void Update();
private:
    int row;
    int column;
    int bomb;
    int **a;
    item *allItems;
    QTime t;
    QTimer *ptimer;
    void setNum(int y, int x);
    int calculateBombs(int x, int y);
    void findWhiteCubes(int x, int y);
    void initMatrix();
};

#endif // GAMESCENE_H
