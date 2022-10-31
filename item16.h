#ifndef ITEM16_H
#define ITEM16_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>



class item16 : public QGraphicsPixmapItem
{
public:
    item16(QString path);
    int flag; //boom or not ;)
    void setNum(int y, int x);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int boomNum; //Count of bombs around
    int isFlagOrWhiteBlock; //0 СѓРєР°Р·С‹РІР°РµС‚ РЅР° СЃРѕСЃС‚РѕСЏРЅРёРµ, РЅР° РєРѕС‚РѕСЂРѕРµ РЅРµ Р±С‹Р» РЅР°Р¶Р°С‚ С‰РµР»С‡РѕРє, 1 СѓРєР°Р·С‹РІР°РµС‚, С‡С‚Рѕ С„Р»Р°Рі РІСЃС‚Р°РІР»РµРЅ, Р° 2 СѓРєР°Р·С‹РІР°РµС‚, С‡С‚Рѕ РїСЂРё РЅР°Р¶Р°С‚РёРё РѕРЅ СЃС‚Р°Р» Р±РµР»С‹Рј.
    int spreadFlag; //Р Р°СЃРїСЂРѕСЃС‚СЂР°РЅРёР»СЃСЏ Р»Рё С‚РµРєСѓС‰РёР№ Р±Р»РѕРє?
    int m_x; // РђР±СЃС†РёСЃСЃР° С‚РµРєСѓС‰РµРіРѕ Р±Р»РѕРєР°
    int m_y; // РћСЂРґРёРЅР°С‚Р° С‚РµРєСѓС‰РµРіРѕ Р±Р»РѕРєР°
};

#endif
