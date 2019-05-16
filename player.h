#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <vector>
#include "platform.h"

class Player: public  QObject, public QGraphicsPixmapItem{
Q_OBJECT
public:
    Player();
    bool rofl=true;
    int levelLength = 3250;
    bool gameEnded = false;

    const int JUMP_HEIGHT=20;
    const int SPEED=3;
    int HEIGHT=45;
    int LENGTH=30;
    QString player_right = ":/images/player_right.png";
    QString player_left = ":/images/player.png";
    const double PISTOL_TO_BODY_HEIGHT_RATIO=0.7;//1=head, 0=feet
    bool init;
    double absoluteX;
    double absoluteY;

    std::vector<Platform*> activeMap;
    std::vector<Platform*> inActiveMap;

    QGraphicsTextItem * lose = new QGraphicsTextItem;
    QGraphicsTextItem * win = new QGraphicsTextItem;
    QGraphicsTextItem * peresda4a = new QGraphicsTextItem;
    QGraphicsTextItem * zakril = new QGraphicsTextItem;

    int verticalVelocity;
    bool jumping;
    int horisontalVelocity;
    bool facingRight;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    bool isOnTheGround();
    bool canMoveHorizontally(int distance);
    void moveHorizontally(int distance);
    bool canMoveUpwards(int distance);
    void jump();
    void shoot();

public slots:
    void move();
};


#endif // PLAYER_H
