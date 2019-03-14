#include<QTimer>
#include"bullet.h"
#include<QGraphicsScene>
#include<QDebug>

Bullet::Bullet(bool facingRight, double x, double y)
{
    setRect(x, y, LENGTH, HEIGHT);
    this->facingRight=facingRight;
    QTimer * timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Bullet::collapse()
{

}

void Bullet::hit()
{

}

void Bullet::move()
{
    if(facingRight){
        setPos(x()+SPEED, y());
    }else{
        setPos(x()-SPEED, y());
    }
    if(x()>800 || x()<-800){
        scene()->removeItem(this);
        delete this;
    }
    qDebug()<<x();
}

