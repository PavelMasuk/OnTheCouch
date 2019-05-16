#include<QTimer>
#include"bullet.h"
#include<QGraphicsScene>
#include<QDebug>

Bullet::Bullet(bool facingRight, double x, double y)
{
    QPixmap bullet_image(":/images/bullet.png");
    setPixmap(bullet_image.QPixmap::scaled(30, 30, Qt::KeepAspectRatio));
    this->facingRight=facingRight;
    if(!facingRight){
        setRotation(180);
    }
    QTimer * timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Bullet::collapse()
{

}

void Bullet::hit()
{
    scene()->removeItem(this);
    delete this;
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
    if(collidingItems().size()>0){
        this->hit();
    }
}

