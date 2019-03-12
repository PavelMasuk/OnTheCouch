#include "dolboeb.h"
#include "bullet.h"
#include <QKeyEvent>
#include<QTimer>
#include<QDebug>
#include<QGraphicsScene>

Dolboeb::Dolboeb()
{
    setRect(0,0,LENGTH,HEIGHT);
    verticalVelocity=0;
    horisontalVelocity=0;
    facingRight=true;
    jumping=false;
    QTimer * timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Dolboeb::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left){
        facingRight=false;
        horisontalVelocity=-SPEED;
    }
    if(event->key()==Qt::Key_Right){
        facingRight=true;
        horisontalVelocity=SPEED;
    }
    if(event->key()==Qt::Key_Up){
            jumping=true;
    }
    if(event->key()==Qt::Key_Space){
        double bulletX;
        double bulletY=y()+((1-PISTOL_TO_BODY_HEIGHT_RATIO)*HEIGHT)-Bullet::HEIGHT;
        if(facingRight){
            bulletX=x()+LENGTH;
        }else{
            bulletX=x();
        }

        Bullet * bullet=new Bullet(facingRight, bulletX, bulletY);
        scene()->addItem(bullet);
    }
}

void Dolboeb::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Left){
        horisontalVelocity=0;
    }
    if(event->key()==Qt::Key_Right){
        horisontalVelocity=0;
    }
    if(event->key()==Qt::Key_Up){
        jumping=false;
    }
}

bool Dolboeb::isOnTheGround()
{
    if(y()>100)
        return true;
    return false;
}

void Dolboeb::jump()
{
    if(isOnTheGround())
        verticalVelocity=JUMP_HEIGHT;
}

void Dolboeb::shoot()
{
    //add animation

}

void Dolboeb::move()
{
    if(jumping){
        jump();
    }
    setPos(x()+horisontalVelocity,y()-verticalVelocity);
    if(!isOnTheGround()){
        verticalVelocity-=1;
    }else{
        verticalVelocity=0;
        //add set pos on top of the ground to avoid penetrating the ground after a big fall
    }
}

