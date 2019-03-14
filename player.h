#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <vector>
#include "platform.h"

class Player: public  QObject, public QGraphicsRectItem{
Q_OBJECT
public:
    Player();
    const int JUMP_HEIGHT=20;
    const int SPEED=3;
    const int HEIGHT=45;
    const int LENGTH=30;
    const double PISTOL_TO_BODY_HEIGHT_RATIO=0.7;//1=head, 0=feet

    double absoluteX;
    double absoluteY;

    std::vector<Platform*> activeMap;

    int verticalVelocity;
    bool jumping;
    int horisontalVelocity;
    bool facingRight;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    bool isOnTheGround();
    void jump();
    void shoot();

public slots:
    void move();
};


#endif // PLAYER_H
