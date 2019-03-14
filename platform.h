#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsRectItem>
#include<QObject>

class Platform: public  QObject, public QGraphicsRectItem{
Q_OBJECT
public:
    double height;
    double length=10;
    int playerSpeed;
    double absoluteX;
    double absoluteY;
    std::string source;

    Platform(double length, double height, std::string source, int playerSpeed, double absoluteX, double absoluteY);
    void collapse();
public slots:
    void move(bool moveLeft);
};

#endif // PLATFORM_H
