#include<QTimer>
#include"platform.h"
#include<QGraphicsScene>
#include<QDebug>


Platform::Platform(double length, double height, std::string source, int playerSpeed, double absoluteX, double absoluteY)
{
    this->height=height;
    this->length=length;
    this->source=source;
    this->playerSpeed=playerSpeed;
    this->absoluteX=absoluteX;
    this->absoluteY=absoluteY;
    setRect(length, height, absoluteX, absoluteY);
}

void Platform::move(bool moveLeft)
{
    if(moveLeft){
        absoluteX-=playerSpeed;
    }else{
        absoluteX+=playerSpeed;
    }

    if(x()<-200 || x()>1000){
        collapse();
    }
}

void Platform::collapse()
{
    scene()->removeItem(this);
    delete this;
}
