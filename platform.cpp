#include<QTimer>
#include"platform.h"
#include<QGraphicsScene>
#include<QDebug>


Platform::Platform(double absoluteX, double absoluteY, double length, double height, std::string source, bool isFirst)
{  
    this->isFirst=isFirst;
    this->init = true;
    this->height=height;
    this->length=length;
    this->source=source;
    this->absoluteX=absoluteX;
    this->absoluteY=absoluteY;
    QPixmap platform_image(":/images/orange.jpg");
    setPixmap(platform_image.QPixmap::scaled(length, height));
    //setRect(absoluteX, absoluteY, length, height);

}

void Platform::move(double distance)
{
    if(this->isFirst && this->init){
        this->init = false;
        setPos(-1000, 150);
    }
    setPos(x()-distance, y());
}

void Platform::collapse()
{
    //qDebug()<<"COLLAPSE---------------------------------";
    scene()->removeItem(this);
    //delete this;
}
