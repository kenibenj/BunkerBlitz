#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int

#include <QDebug>
Enemy::Enemy(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {
    //set random position
    int random_number = rand() % 700;
    setPos(random_number, 0);

    // drew the rect
   // setRect(0, 0, 100, 100);
    setPixmap(QPixmap(":/images/enemy.png"));
    setTransformOriginPoint(50, 50);
    setRotation(180);

    // connect
   // QTimer* enemytimer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(14);
}


void Enemy::move() {
    // move enemy down
    setPos(x(), y() + 3);
    //need to change below to window dimensions + rect().height() 
    if (pos().y()  < 0) {
        scene()->removeItem(this);
        delete timer;
        delete this;

    }
}
