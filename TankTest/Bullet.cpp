#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QMovie>
#include <QLabel>
#include <Explosion.h>
#include "Enemy.h"
#include "wall.h"



Bullet::Bullet(char direction, QPointF cursorScenePos, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    //draw bullet
    direct = direction;
    setPixmap(QPixmap(":/images/Bullet.jpg"));
    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);
}

// Four-directional shooting that uses the direction the tank is facing
void Bullet::fireDirectional () {

    // Set speed of bullet
    speed = 6;

    // Calculate x and y velocity
    switch (direct) {
    case 'w':
        dx = 0;
        dy = speed * -1;
        setRotation(0);
        break;
    case 'a':
        dx = speed * -1;
        dy = 0;
        setRotation(270);
        break;
    case 's':
        dx = 0;
        dy = speed;
        setRotation(180);
        break;
    case 'd':
        dx = speed;
        dy = 0;
        setRotation(90);
        break;
    }

    //connect
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(17);
}

// Swivel shooting that uses the mouse cursor
void Bullet::fireSwivel() {

    // Get cursor position when bullet is created
    QPoint cursorPos = QCursor::pos();
    QPointF cursorScenePos = scene()->views().first()->mapFromGlobal(cursorPos);
    float angle = atan2(cursorScenePos.y() - y(), cursorScenePos.x() - x());
    float angleDegrees = angle * (180 / M_PI);

    // Set speed of bullet
    speed = 20;

    // Calculate x and y velocity
    dx = speed * cos(angle);
    dy = speed * sin(angle);

    // Trig shenanigans. Not sure why angleDegrees by itself doesn't work; I dislike just tacking on 90 degrees but it's fine for now.
    setRotation(angleDegrees + 90);

    //connect
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(17);

}

void Bullet::move() {
    //Collison check for enemies
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            
            //delete enemy
            scene()->removeItem(colliding_items[i]);

            //Create explosion on collision
            Explosion* explosion = new Explosion(colliding_items[i]->pos());
            scene()->addItem(explosion);

            //delete bullet
            scene()->removeItem(this);
            delete this;

            //Delete enemy
            delete(colliding_items[i]);
            return;

            // Delete Explosion, I do not know if this code is needed. - Michael
            scene()->removeItem(explosion);
            delete explosion;

        }
        // You could also incorporate the explosion effect into the wall
        if (typeid(*(colliding_items[i])) == typeid(Wall)) {

            //disconnect signal from timer
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move()));
            timer->stop();

            //delete bullet and wall
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            //Delete objects
            delete(colliding_items[i]);
            delete(this);
            return;
        }
    }

    // Move bullet towards the direction of the cursor when it was fired
    setPos(x() + dx, y() + dy);

    // Remove bullet if it goes out of bounds
    if ((pos().y() + boundingRect().height() < 0) || (pos().y() > scene()->height()) || (pos().x() + boundingRect().width() < 0) || (pos().x() > scene()->width())) {
        scene()->removeItem(this);
        delete this;
    }
}
