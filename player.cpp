#include "player.h"
#include "bullet.h"
#include <QKeyEvent>
#include<QTimer>
#include<QDebug>
#include<QGraphicsScene>

Player::Player()
{
    setRect(0,0,LENGTH,HEIGHT);
    verticalVelocity=0;
    horisontalVelocity=0;
    facingRight=true;
    jumping=false;

    absoluteX=0;
    absoluteY=100;

    activeMap.push_back(new Platform(1000, 150, 1000, 200, ""));
    activeMap.push_back(new Platform(1300, 100, 10, 50, ""));

    QTimer * timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Player::keyPressEvent(QKeyEvent *event)
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

void Player::keyReleaseEvent(QKeyEvent *event){
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

bool Player::isOnTheGround()
{
    if(y()>100)
        return true;
    return false;
}

void Player::jump()
{
    if(isOnTheGround())
        verticalVelocity=JUMP_HEIGHT;
}

void Player::shoot()
{
    //add animation

}

void Player::move()
{

    absoluteX+=horisontalVelocity;
    for(Platform* platform : activeMap){
        //qDebug()<<"should be on screen";
        //qDebug()<<platform->absoluteX;
        qDebug()<<absoluteX;
        //qDebug()<<platform->absoluteX+platform->length;
        //qDebug()<<absoluteX-500;
        if(platform->absoluteX<absoluteX+600 && platform->absoluteX+platform->length>absoluteX-500){
            if(!platform->isAddedToTheScene){
                qDebug()<<"ADD ITEM TO THE SCENE-------------------------";
                scene()->addItem(platform);
                platform->isAddedToTheScene=true;
            }
        }else{
            if(platform->isAddedToTheScene){
                platform->isAddedToTheScene=false;
                platform->collapse();
            }
        }
    }

    if(jumping){
        jump();
    }
    setPos(x(),y()-verticalVelocity);
    if(!isOnTheGround()){
        verticalVelocity-=1;
    }else{
        verticalVelocity=0;
        //add set pos on top of the ground to avoid penetrating the ground after a big fall
    }
    for(Platform* platform : activeMap){
        if(platform->isAddedToTheScene){
            platform->move(horisontalVelocity);
        }
    }

}


