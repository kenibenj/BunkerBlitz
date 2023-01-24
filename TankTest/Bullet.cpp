#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
Bullet::Bullet()
{
    //draw bullet
    setRect(0, 0, 14, 28);

    //connect
    //QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
     

    timer->start(7);
}

void Bullet::move() {
    //move bullet up
    setPos(x(), y() - 10);
    if (pos().y() + rect().height()< 0) {
        scene()->removeItem(this);
        delete timer;
        delete this;
    }
}
