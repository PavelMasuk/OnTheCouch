#include <QApplication>
#include <QGraphicsScene>
#include "player.h"
#include <QGraphicsView>

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
    QPixmap bg(":/images/background.png");
    view->setBackgroundBrush(bg.QPixmap::scaled(1000, 1000, Qt::KeepAspectRatio));
    scene->setStickyFocus(true);
    view->show();
    return a.exec();
}
