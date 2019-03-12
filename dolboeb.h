#ifndef DOLBOEB_H
#define DOLBOEB_H

#include <QGraphicsRectItem>
#include<QObject>

class Dolboeb: public  QObject, public QGraphicsRectItem{
Q_OBJECT
public:
    Dolboeb();
    int JUMP_HEIGHT=20;
    int verticalVelocity=0;
    int horisontalVelocity=0;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

public slots:
    void moveVertically();
};


#endif // DOLBOEB_H
