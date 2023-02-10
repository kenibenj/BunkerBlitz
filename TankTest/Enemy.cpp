#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int

#include <QDebug>
Enemy::Enemy(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {
    //set random position
    int random_number = rand() % 700;
    distance = 5;

    setPos(random_number, 0);

    // drew the rect
   // setRect(0, 0, 100, 100);
    setPixmap(QPixmap(":/images/enemy.png"));
    setTransformOriginPoint(50, 50);
    setRotation(180);

    // connect
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(17);
}


void Enemy::move() {
    // Check if the enemy has reached the edge of the map
    if (pos().x() < 0 || pos().x() + boundingRect().width() > scene()->width() ||
        pos().y() < 0 || pos().y() + boundingRect().height() > scene()->height()) {
        // Generate a new random direction
        int randomNum = rand() % 4;

        // Move enemy in a randomly chosen direction
        if (randomNum == 0) {
            if (pos().y() > 0) {
                setPos(x(), y() - distance);
                setRotation(0); // facing upwards
            }
        }
        else if (randomNum == 1) {
            if (pos().x() > 0) {
                setPos(x() - distance, y());
                setRotation(270); // facing left
            }
        }
        else if (randomNum == 2) {
            if (pos().y() + distance < scene()->height() - boundingRect().height()) {
                setPos(x(), y() + distance);
                setRotation(180); // facing downwards
            }
        }
        else if (randomNum == 3) {
            if (pos().x() + distance < scene()->width() - boundingRect().width()) {
                setPos(x() + distance, y());
                setRotation(90); // facing right
            }
        }
    }
    else {
        // Continue moving in the same direction
        if (rotation() == 0) {
            setPos(x(), y() - distance);
        }
        else if (rotation() == 270) {
            setPos(x() - distance, y());
        }
        else if (rotation() == 180) {
            setPos(x(), y() + distance);
        }
        else if (rotation() == 90) {
            setPos(x() + distance, y());
        }
    }
}
