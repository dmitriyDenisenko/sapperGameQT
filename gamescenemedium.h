
#include <QObject>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>
#include <QtGlobal>
#include <QAbstractItemModel>

class GameSceneMedium : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameSceneMedium(QObject *parent = nullptr);
    void initImage();

    static int index;
public slots:
    void Update();
private:
    QTime t;
    QTimer *ptimer;
};

