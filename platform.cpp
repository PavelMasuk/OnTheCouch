#include<QTimer>
#include"platform.h"
#include<QGraphicsScene>
#include<QDebug>


Platform::Platform(double absoluteX, double absoluteY, double length, double height, std::string source)
{
    this->height=height;
    this->length=length;
    this->source=source;
    this->absoluteX=absoluteX;
    this->absoluteY=absoluteY;
    setRect(600, absoluteY, length, height);
}

void Platform::move(double distance)
{
    setPos(x()-distance, y());
}

void Platform::collapse()
{
    qDebug()<<"COLLAPSE---------------------------------";
    scene()->removeItem(this);
    //delete this;
}
