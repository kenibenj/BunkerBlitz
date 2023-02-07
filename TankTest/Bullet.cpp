#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "Enemy.h"



Bullet::Bullet(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    //draw bullet
    setPixmap(QPixmap(":/images/Bullet.jpg"));


    //setRect(0, 0, 14, 28);

    //connect
    //QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
     

    timer->start(7);
}

void Bullet::move() {
    //Collison check for enemies
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            //delete bullet and enemy
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //Delete objects
            delete(colliding_items[i]);
            delete(timer);
            delete(this);
            return;
        }
    }
    //move bullet up
    setPos(x(), y() - 5);
    if (pos().y() < 0) {
        scene()->removeItem(this);
        delete timer;
        delete this;
    }
}
