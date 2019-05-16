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
        this->HEIGHT *= 1;
        this->LENGTH *= 1;
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
    Platform* p1 = new Platform(0, 0, 40, 10, "orange.jpg", false);
            Platform* p11 = new Platform(100, 100, 100, 100, "orange.jpg", false);
            Platform* p12 = new Platform(150, 50, 100, 100, "orange.jpg", false);
            Platform* p13 = new Platform(200, 0, 100, 100, "orange.jpg", false);
            Platform* p14 = new Platform(250, -50, 100, 100, "orange.jpg", false);

            Platform* p21 = new Platform(450, -100, 100, 10, "orange.jpg", false);
            Platform* p22 = new Platform(560, -100, 90, 10, "orange.jpg", true);
            Platform* p23 = new Platform(650, -100, 100, 10, "orange.jpg", false);
            Platform* p24 = new Platform(760, -100, 90, 10, "orange.jpg", true);
            Platform* p25 = new Platform(850, -100, 100, 10, "orange.jpg", false);
            Platform* p26 = new Platform(960, -100, 90, 10, "orange.jpg", true);
            Platform* p27 = new Platform(1050, -100, 100, 10, "orange.jpg", false);
            Platform* p28 = new Platform(1160, -100, 90, 10, "orange.jpg", true);

            Platform* p29 = new Platform(1260, -100, 300, 10, "orange.jpg", false);

            Platform* p30  = new Platform(1950, -200, 650, 100, "orange.jpg", true, true, true, true);
            Platform* p31  = new Platform(1950, -100, 650, 10, "orange.jpg", false);
            Platform* p32  = new Platform(1950, -450, 700, 250, "orange.jpg", false);
            activeMap.push_back(p31);
            activeMap.push_back(p32);


            Platform* p16 = new Platform(1400, -400, 3000, 10, "orange.jpg", false);

            Platform* p17 = new Platform(1600, -150, 50, 10, "orange.jpg", false);
            Platform* p18 = new Platform(1700, -100, 50, 10, "orange.jpg", false);
            Platform* p19 = new Platform(1800, -50, 50, 10, "orange.jpg", false);
            Platform* p20 = new Platform(1900, 0, 50, 10, "orange.jpg", false);


            Platform* p2 = new Platform(-500, 150, 2200, 500, "orange.jpg", false);
            Platform* p3 = new Platform(1300, 200, 100, 200, "orange.jpg", false);
            Platform* p4 = new Platform(1450, 100, 500, 50, "orange.jpg", false);
            Platform* p5 = new Platform(2000, -500, 1000, 10, "orange.jpg", false);

            Platform* p7 = new Platform(2600, 150, 90, 300, "orange.jpg", false);
            Platform* p8 = new Platform(2800, 150, 90, 300, "orange.jpg", false);
            Platform* p9 = new Platform(3000, 150, 90, 300, "orange.jpg", false);
            Platform* p10 = new Platform(3200, 150, 90, 300, "orange.jpg", false);

            activeMap.push_back(p1);
            activeMap.push_back(p2);
            activeMap.push_back(p3);
            activeMap.push_back(p4);
            activeMap.push_back(p5);

            activeMap.push_back(p7);
            activeMap.push_back(p8);
            activeMap.push_back(p9);
            activeMap.push_back(p10);
            activeMap.push_back(p11);
            activeMap.push_back(p12);
            activeMap.push_back(p13);
            activeMap.push_back(p14);
            activeMap.push_back(p16);
            activeMap.push_back(p16);
            activeMap.push_back(p17);
            activeMap.push_back(p18);
            activeMap.push_back(p19);
            activeMap.push_back(p20);
            activeMap.push_back(p21);

            activeMap.push_back(p22);
            activeMap.push_back(p23);
            activeMap.push_back(p24);
            activeMap.push_back(p25);
            activeMap.push_back(p26);
            activeMap.push_back(p27);
            activeMap.push_back(p28);
            activeMap.push_back(p29);

            activeMap.push_back(p30);


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
    if(event->key()==Qt::Key_A){
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
    if(event->key()==Qt::Key_D){
        facingRight=true;
        QPixmap player_image(player_right);
        setPixmap(player_image.QPixmap::scaled(LENGTH, HEIGHT));
        horisontalVelocity=SPEED;
    }
    if(event->key()==Qt::Key_Up){
            jumping=true;
    }
    if(event->key()==Qt::Key_W){
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
    if(event->key()==Qt::Key_Q){
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


