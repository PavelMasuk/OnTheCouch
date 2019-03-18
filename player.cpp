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

    activeMap.push_back(new Platform(400, 100, 10, 100, ""));
    activeMap.push_back(new Platform(1000, 150, 1000, 200, ""));
    activeMap.push_back(new Platform(1300, -50, 100, 200, ""));
    activeMap.push_back(new Platform(1450, -100, 500, 50, ""));

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
    for(Platform* platform : activeMap){
        if(absoluteX>platform->absoluteX-LENGTH && absoluteX< platform->absoluteX+platform->length){
            if(y()<platform->absoluteY+platform->height && y()+HEIGHT>=platform->absoluteY){
                setPos(x(), platform->absoluteY-HEIGHT);
                return  true;
            }
        }
    }
    if(y()>=150){
        setPos(x(), 150);
        return true;
    }
    return false;
}

bool Player::canMoveHorizontally(int distance){
    bool canMove=true;
    for(Platform* platform : activeMap){
        if(platform->isAddedToTheScene){
            if(absoluteX+distance+LENGTH>=platform->absoluteX && absoluteX+distance<= platform->absoluteX+platform->length+3){
                if(y()<platform->absoluteY+platform->height && y()+HEIGHT>platform->absoluteY){
                    canMove=false;
                }
            }
        }
    }
    return canMove;
}

void Player::moveHorizontally(int distance)
{
    absoluteX+=horisontalVelocity;
    for(Platform* platform : activeMap){
        if(platform->isAddedToTheScene){
            platform->move(distance);
        }
    }
}

bool Player::canMoveUpwards(int distance){
    bool canMove=true;
    for(Platform* platform : activeMap){
        if(platform->isAddedToTheScene){
            if(absoluteX>=platform->absoluteX-LENGTH && absoluteX<= platform->absoluteX+platform->length){
                if(y()-distance<platform->absoluteY+platform->height && y()-distance+HEIGHT>platform->absoluteY){
                    canMove=false;
                }
            }
        }
    }
    return canMove;
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
    //map loading
    for(Platform* platform : activeMap){
        //qDebug()<<absoluteX;
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
    if(isOnTheGround()){
        if(verticalVelocity<0){
            verticalVelocity=0;
        }
    }else{
        verticalVelocity-=1;
    }

    if(!canMoveUpwards(verticalVelocity) && verticalVelocity>0){
        verticalVelocity=0;
    }


    setPos(x(),y()-verticalVelocity);
    isOnTheGround(); //protection from going through the ground for a second after a big fall

    if(canMoveHorizontally(horisontalVelocity)){
        moveHorizontally(horisontalVelocity);
    }
}


