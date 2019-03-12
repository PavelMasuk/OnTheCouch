#include "dolboeb.h"
#include <QKeyEvent>
#include<QTimer>
#include<QDebug>

Dolboeb::Dolboeb()
{
    setRect(0,0,100,100);
    QTimer * timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(moveVertically()));
    timer->start(10);
}

void Dolboeb::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left){
        horisontalVelocity=-3;
    }
    if(event->key()==Qt::Key_Right){
        horisontalVelocity=3;
    }
    if(event->key()==Qt::Key_Space){
        verticalVelocity=JUMP_HEIGHT;
    }
}

void Dolboeb::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Left){
        horisontalVelocity=0;
    }
    if(event->key()==Qt::Key_Right){
        horisontalVelocity=0;
    }
}

void Dolboeb::moveVertically()
{
    setPos(x()+horisontalVelocity,y()-verticalVelocity);
    if(y()<100){
        verticalVelocity-=1;
    }else{
        verticalVelocity=0;
        setPos(x(),100);
    }
    if(y()>100){
        setPos(x(),100);
    }
}


