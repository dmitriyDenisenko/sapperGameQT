#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>



class item : public QGraphicsPixmapItem
{
public:
    item(QString path);
    int flag;
    void setNum(int y, int x);
private:
    void calculateBombs(int x, int y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void findWhiteCubes(int x, int y);
    int boomNum;
    int isFlagOrWhiteBlock;
    int spreadFlag; //Is the current block an element of recursion
    int m_x;
    int m_y;
};

#endif // MYITEM_H
