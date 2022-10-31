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
};

#endif // GAMESCENE_H
