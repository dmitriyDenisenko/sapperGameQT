#include "item.h"
#include <unistd.h>
#include <QGraphicsSceneMouseEvent>
#include <qmessagebox.h>
#include <qmessagebox.h>
#include <QMessageLogger>
#include <QMessageLogger>
#include <qlogging.h>

int gameOverFlag = 0;
int a[8][8];
int flagNumb;
extern int Click;
extern item *allItems[64];

item::item(QString path)
{
    this->setPixmap(QPixmap(path));
    isFlagOrWhiteBlock = 0;
    spreadFlag = 0;
    flag = 0;
}

item::item()
{
    this->setPixmap(QPixmap(":/source_pic/pink cube"));
    isFlagOrWhiteBlock = 0;
    spreadFlag = 0;
    flag = 0;
}
void item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && flag == 0 && isFlagOrWhiteBlock == 0)
    {
        m_x = this->pos().x();
        m_y = this->pos().y();
        setNum(m_y/50, m_x/50);

    }else if(event->button() == Qt::LeftButton && flag == 1 && isFlagOrWhiteBlock == 0)
    {
        this->setPixmap(QPixmap(":/source_pic/bomb"));
        gameOverFlag = 1;

    }else if(event->button() == Qt::RightButton && flag == 1)
    {
        if(isFlagOrWhiteBlock == 0)
        {
            this->setPixmap(QPixmap(":/source_pic/flag"));
            isFlagOrWhiteBlock++;
            flagNumb++;

        }else if(isFlagOrWhiteBlock == 1)
        {
            this->setPixmap(QPixmap(":/source_pic/pink cube"));
            isFlagOrWhiteBlock--;
            flagNumb--;
        }

    }else if(event->button() == Qt::RightButton && flag == 0)
    {
        if(isFlagOrWhiteBlock == 0)
        {
            this->setPixmap(QPixmap(":/source_pic/flag"));
            isFlagOrWhiteBlock++;
            flagNumb--;
        }else if(isFlagOrWhiteBlock == 1)
        {
           this->setPixmap(QPixmap(":/source_pic/pink cube"));
           isFlagOrWhiteBlock--;
           flagNumb++;
        }
    }
    Click++;
}

int item::getIsFlagOrWhiteBlock(){
    return isFlagOrWhiteBlock;
}
void item::setIsFlagOrWhiteBlock(int flag){
    isFlagOrWhiteBlock = flag;
}
int item::getSpreadFlag(){
    return spreadFlag;
}
void item::setSpreadFlag(int flag){
    spreadFlag = flag;
}
