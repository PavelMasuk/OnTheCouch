#include <QApplication>
#include <QGraphicsScene>
#include "dolboeb.h"
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene * scene=new QGraphicsScene();

    Dolboeb * dolboeb=new Dolboeb();
    dolboeb->setFlag(QGraphicsItem::ItemIsFocusable);
    dolboeb->setFocus();
    scene->addItem(dolboeb);
    QGraphicsView * view=new QGraphicsView(scene);
    view->setFixedSize(800,800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSceneRect(-200,-300,600,500);
    view->show();
    return a.exec();
}
