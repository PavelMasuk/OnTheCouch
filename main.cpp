#include <QApplication>
#include <QGraphicsScene>
#include "dolboeb.h"
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene * scene=new QGraphicsScene();

    Dolboeb * dolboeb=new Dolboeb();
    dolboeb->setRect(0,0,100,100);
    dolboeb->setFlag(QGraphicsItem::ItemIsFocusable);
    dolboeb->setFocus();
    scene->addItem(dolboeb);
    QGraphicsView * view=new QGraphicsView(scene);
    view->setFixedSize(800,800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    return a.exec();
}
