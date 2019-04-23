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
    if(absoluteX>=600){
        QPixmap platform_image(":/images/bricks.jpg");
        setPixmap(platform_image.QPixmap::scaled(length, height));
        //setRect(600, absoluteY, length, height);
    }else{
        QPixmap bullet_image(":/images/bricks.jpg");
        setPixmap(bullet_image.QPixmap::scaled(length, height));
        //setRect(absoluteX, absoluteY, length, height);
    }
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
