#include<QTimer>
#include"platform.h"
#include<QGraphicsScene>
#include<QDebug>


Platform::Platform(double absoluteX, double absoluteY, double length, double height, QString source, bool noCollisionBox)
{  
    this->noCollisionBox=noCollisionBox;
    this->init = true;
    this->height=height;
    this->length=length;
    this->source=":/images/"+source;
    this->absoluteX=absoluteX;
    this->absoluteY=absoluteY;
    QPixmap platform_image(this->source);
    setPixmap(platform_image.QPixmap::scaled(length, height));
    setPos(this->absoluteX, this->absoluteY);

}

void Platform::move(double distance)
{
    setPos(x()-distance, y());
}

void Platform::collapse()
{
    //qDebug()<<"COLLAPSE---------------------------------";
    scene()->removeItem(this);
    //delete this;
}
