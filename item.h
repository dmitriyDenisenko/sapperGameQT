#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>



class item : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    item();
    item(QString path);
    int flag;
    int getIsFlagOrWhiteBlock();
    void setIsFlagOrWhiteBlock(int flag);
    int getSpreadFlag();
    void setSpreadFlag(int flag);
signals:
    void setNum(int y,int x);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int boomNum;
    int isFlagOrWhiteBlock;
    int spreadFlag; //Is the current block an element of recursion
    int m_x;
    int m_y;
};

#endif // MYITEM_H
