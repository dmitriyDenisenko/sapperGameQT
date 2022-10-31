#include "gamebutton.h"

GameButton::GameButton(const QString &text){
    this->setText(text);
}


void GameButton::setId(int id){
    this->id = id;
}


