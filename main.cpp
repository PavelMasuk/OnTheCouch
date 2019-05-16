#include <QApplication>
#include <QGraphicsScene>
#include "player.h"
#include <QGraphicsView>
#include <QGraphicsTextItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene * scene=new QGraphicsScene();

    Player * player=new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    QGraphicsView * view=new QGraphicsView(scene);
    //view->setFixedSize(800,800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSceneRect(-200,-300,600,500);
    //view->setMaximumSize(1000, 1200);
    //view->setMinimumSize(600, 500);
    QPixmap bg(":/images/bg.png");
    view->setBackgroundBrush(bg.QPixmap::scaled(2000, 1000, Qt::KeepAspectRatio));
    scene->setStickyFocus(true);
    view->show();
    return a.exec();
}
