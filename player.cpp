#include "player.h"
#include "bullet.h"
#include <QKeyEvent>
#include<QTimer>
#include<QDebug>
#include<QColor>
#include<QGraphicsScene>

Player::Player()
{
    if(rofl){
        this->HEIGHT *= 10;
        this->LENGTH *= 10;
        this->player_right = ":/images/iliin_right.png";
        this->player_left = ":/images/iliin_left.png";
    }
    QPixmap player_image(player_right);
    setPixmap(player_image.QPixmap::scaled(LENGTH, HEIGHT));
    verticalVelocity=0;
    horisontalVelocity=0;
    facingRight=true;
    jumping=false;
    absoluteX=0;
    absoluteY=100;
    this->init = true;
    Platform* finish = new Platform(this->levelLength, -2000, 10, 10000, "finish.jpg", false, false, false, true);
    activeMap.push_back(finish);
    Platform* p1 = new Platform(400, 100, 10, 100, "orange.jpg");
    Platform* p2 = new Platform(-1000, 150, 3000, 500, "orange.jpg");
    Platform* p3 = new Platform(1300, -50, 100, 200, "orange.jpg");
    Platform* p4 = new Platform(1450, -100, 500, 50, "orange.jpg");
    Platform* p5 = new Platform(2000, -50, 500, 50, "orange.jpg");
    activeMap.push_back(p1);
    activeMap.push_back(p2);
    activeMap.push_back(p3);
    activeMap.push_back(p4);
    activeMap.push_back(p5);


    this->lose->setScale(4);
    this->lose->setPlainText("YOU LOSE");
    this->lose->setDefaultTextColor(QColor(255,0,0));
    this->win->setScale(4);
    this->win->setPlainText("YOU WIN");
    this->win->setDefaultTextColor(QColor(0,255,0));
    this->peresda4a->setScale(10);
    this->peresda4a->setPlainText("ПЕРЕСДАЧА");
    this->peresda4a->setDefaultTextColor(QColor(255,0,0));
    this->zakril->setScale(4);
    this->zakril->setPlainText("ЗАКРЫЛ!");
    this->zakril->setDefaultTextColor(QColor(0,255,0));

    QTimer * timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left){
        facingRight=false;
        QPixmap player_image(player_left);
        setPixmap(player_image.QPixmap::scaled(LENGTH, HEIGHT));
        horisontalVelocity=-SPEED;
    }
    if(event->key()==Qt::Key_Right){
        facingRight=true;
        QPixmap player_image(player_right);
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
                if(!platform->noCollisionBoxTop){
                setPos(x(), platform->absoluteY-HEIGHT);
                return  true;
                }
            }
        }
    }
    if(y()>200){
        if(rofl){
        this->peresda4a->setPos(-600,-200);
        scene()->addItem(this->peresda4a);
        }else{
            this->lose->setPos(-30,-100);
                    scene()->addItem(this->lose);
        }
        this->gameEnded = true;
    }
    return false;
}

bool Player::canMoveHorizontally(int distance){
    bool canMove=true;
    for(Platform* platform : activeMap){
        if(platform->isAddedToTheScene){
            if(!(distance>0 && platform->noCollisionBoxLeft) && !(distance<0 && platform->noCollisionBoxRight)){
            if(absoluteX+distance+LENGTH>=platform->absoluteX && absoluteX+distance<= platform->absoluteX+platform->length+3){
                if(y()<platform->absoluteY+platform->height && y()+HEIGHT>platform->absoluteY){
                    canMove=false;
                }
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
                    if(!platform->noCollisionBoxBottom)
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
        if(this->absoluteX+this->LENGTH>this->levelLength){
            if(rofl){
            this->zakril->setPos(-30,-100);
            scene()->addItem(this->zakril);
            }else{
                this->win->setPos(-30,-100);
                            scene()->addItem(this->win);
            }
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


