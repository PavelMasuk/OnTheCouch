#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsRectItem>
#include<QObject>

class Platform: public  QObject, public QGraphicsRectItem{
Q_OBJECT
public:
    double height;
    double length=10;
    double absoluteX;
    double absoluteY;
    std::string source;
    double relativeX=0;
    double relativeY=0;

    bool isAddedToTheScene=false;

    Platform(double absoluteX, double absoluteY, double length, double height, std::string source);
    void collapse();
public slots:
    void move(double distance);
};

#endif // PLATFORM_H
