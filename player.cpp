#include "player.h"
#include "bullet.h"
#include <QKeyEvent>
#include<QTimer>
#include<QDebug>
#include<QColor>
#include<QGraphicsScene>

Player::Player()
{
    QPixmap player_image(":/images/player.png");
    setPixmap(player_image.QPixmap::scaled(LENGTH, HEIGHT));
    verticalVelocity=0;
    horisontalVelocity=0;
    facingRight=true;
    jumping=false;
    absoluteX=0;
    absoluteY=100;
    this->init = true;
    Platform* finish = new Platform(this->levelLength, -2000, 10, 10000, "finish.jpg", true);
    activeMap.push_back(finish);
    Platform* p1 = new Platform(400, 100, 10, 100, "orange.jpg", false);
    Platform* p2 = new Platform(-1000, 150, 3000, 500, "orange.jpg", false);
    Platform* p3 = new Platform(1300, -50, 100, 200, "orange.jpg", false);
    Platform* p4 = new Platform(1450, -100, 500, 50, "orange.jpg", false);
    Platform* p5 = new Platform(2000, -50, 500, 50, "orange.jpg", false);
    activeMap.push_back(p1);
    activeMap.push_back(p2);
    activeMap.push_back(p3);
    activeMap.push_back(p4);
    activeMap.push_back(p5);

    QTimer * timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left){
        facingRight=false;
        QPixmap player_image(":/images/player.png");
        setPixmap(player_image.QPixmap::scaled(LENGTH, HEIGHT));
        horisontalVelocity=-SPEED;
    }
    if(event->key()==Qt::Key_Right){
        facingRight=true;
        QPixmap player_image(":/images/player_right.png");
        setPixmap(player_image.QPixmap::scaled(LENGTH, HEIGHT));
        horisontalVelocity=SPEED;
    }
    if(event->key()==Qt::Key_Up){
            jumping=true;
    }
    if(event->key()==Qt::Key_Space){
        double bulletX;
        double bulletY=y();
        if(facingRight){
            bulletX=x()+LENGTH;
            bulletY-=7;
        }else{
            bulletX=x();
            bulletY+=4.75*Bullet::HEIGHT;
        }

        Bullet * bullet=new Bullet(facingRight, bulletX, bulletY);
        bullet->setPos(bulletX,bulletY);
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
    if(y()>200){
        QGraphicsTextItem * lose = new QGraphicsTextItem;
        lose->setPos(-30,-100);
        lose->setScale(4);
        lose->setPlainText("YOU LOSE");
        lose->setDefaultTextColor(QColor(255,0,0));
        scene()->addItem(lose);
        this->gameEnded = true;
    }
    return false;
}

bool Player::canMoveHorizontally(int distance){
    bool canMove=true;
    for(Platform* platform : activeMap){
        if(platform->isAddedToTheScene){
            if(absoluteX+distance+LENGTH>=platform->absoluteX && absoluteX+distance<= platform->absoluteX+platform->length+3){
                if(y()<platform->absoluteY+platform->height && y()+HEIGHT>platform->absoluteY){
                    if(!platform->noCollisionBox)
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
    if(!this->gameEnded){
    //map loading
        if(this->absoluteX>this->levelLength){
            QGraphicsTextItem * win = new QGraphicsTextItem;
            win->setPos(-30,-100);
            win->setScale(4);
            win->setPlainText("YOU WIN");
            win->setDefaultTextColor(QColor(0,255,0));
            scene()->addItem(win);
            this->gameEnded = true;
        }
    for(Platform* platform : activeMap){
        //qDebug()<<absoluteX;
        //if(platform->absoluteX<absoluteX+600 && platform->absoluteX+platform->length>absoluteX-500){
            if(!platform->isAddedToTheScene){
                //qDebug()<<"ADD ITEM TO THE SCENE-------------------------";
                scene()->addItem(platform);
                platform->isAddedToTheScene=true;
            }
        //}else{
            if(platform->isAddedToTheScene){
                //platform->isAddedToTheScene=false;
                //platform->collapse();
            //}
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
}


