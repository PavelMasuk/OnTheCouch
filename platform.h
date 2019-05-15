#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>
#include<QObject>

class Platform: public  QObject, public QGraphicsPixmapItem{
Q_OBJECT
public:
    bool init;
    bool isFirst;
    double height;
    double length=10;
    double absoluteX;
    double absoluteY;
    std::string source;
    double relativeX=0;
    double relativeY=0;

    bool isAddedToTheScene=false;

    Platform(double absoluteX, double absoluteY, double length, double height, std::string source, bool isFirst);
    void collapse();
public slots:
    void move(double distance);
};

#endif // PLATFORM_H
