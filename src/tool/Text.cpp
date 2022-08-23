#include "tool/Text.hpp"

Text::Text(unsigned short x, unsigned short y, QString text){
    this->x = x;
    this->y = y;

    this->text = text;

}

void Text::setText(QString text){
    this->text = text;

}

unsigned short Text::getX(){
    return this->x;

}

unsigned short Text::getY(){
    return this->y;

}

QString Text::getText(){
    return this->text;
    
}