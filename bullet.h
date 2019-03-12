#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include<QObject>

class Bullet: public  QObject, public QGraphicsRectItem{
Q_OBJECT
public:
    const int SPEED=6;
    static const int HEIGHT=5;
    const int LENGTH=10;

    Bullet(bool facingRight, double x, double y);
    bool facingRight;
    void collapse();
    void hit();
public slots:
    void move();
};

#endif // BULLET_H
