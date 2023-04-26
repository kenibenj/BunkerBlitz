#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QMovie>
#include <QLabel>
#include <Explosion.h>
#include "Enemy.h"
#include "Tank.h"
#include "Boss.h"
#include "wall.h"
#include "Spawner.h"
#include "Obstacles.h"
#include "Shield.h"
#include "Ammo.h"
#include "Repair.h"

extern QTimer* enemyTimer;
Bullet::Bullet(QGraphicsItem* tank, char direction, float angle, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    //draw bullet
    direct = direction;
    this->angle = angle;
    this->tank = tank;
    this->setZValue(-4);
    speed = 3;
    damage = 20;

    if (typeid(*(tank)) == typeid(Enemy)) {
        setPixmap(QPixmap(":/images/bulletRed.png"));
    }
    else if (typeid(*(tank)) == typeid(Tank)) {
        setPixmap(QPixmap(":/images/bulletGreen.png"));
    }
    else if (typeid(*(tank)) == typeid(Boss)) {
        setPixmap(QPixmap(":/images/bossBullet.png"));
        damage = 5;
    }
    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);
}

// Swivel shooting that uses the mouse cursor
void Bullet::fireSwivel() {

    float inaccuracyModifier = QRandomGenerator::global()->bounded(-10, 11) / 100.00;
    angle += inaccuracyModifier;
    float angleDegrees = angle * (180 / M_PI);

    // Calculate x and y velocity
    dx = speed * cos(angle);
    dy = speed * sin(angle);

    // Trig shenanigans. Not sure why angleDegrees by itself doesn't work; I dislike just tacking on 90 degrees but it's fine for now.
    setRotation(angleDegrees + 90);

    //connect
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(move()));
    enemyTimer->start(7);

}

void Bullet::move() {
    //Collison check for enemies
    QList<QGraphicsItem*> colliding_items = collidingItems();

    //List doesn't count tank that originally fired bullet. Prevents self-destruct shooting
    colliding_items.removeAll(tank);

    // Iterates through detected objects
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {

            Enemy* enemy = static_cast<Enemy*>(colliding_items[i]);

            QPointF explosionPos;
            explosionPos.setX(colliding_items[i]->pos().x());
            explosionPos.setY(colliding_items[i]->pos().y());

            Explosion* explosion = new Explosion();
            scene()->addItem(explosion);
            explosion->setPos(explosionPos);

            // Reduce enemy's health by bullet's damage
            enemy->takeDamage(damage);
            // Remove bullet from scene
            scene()->removeItem(this);
            delete this;
            // Stop checking for collisions with other enemies
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Boss)) {

            Boss* boss = static_cast<Boss*>(colliding_items[i]);

            QPointF explosionPos;
            explosionPos.setX(colliding_items[i]->pos().x());
            explosionPos.setY(colliding_items[i]->pos().y());

            Explosion* explosion = new Explosion();
            scene()->addItem(explosion);
            explosion->setPos(explosionPos);

            // Reduce enemy's health by bullet's damage
            boss->takeDamage(damage);
            // Remove bullet from scene
            scene()->removeItem(this);
            delete this;
            // Stop checking for collisions with other enemies
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Tank)) {

            Tank* playerTank = static_cast<Tank*>(colliding_items[i]);

            // Reduce enemy's health by bullet's damage
            playerTank->takeDamage(damage);

            // Create explosion on collision
            QPointF explosionPos;
            explosionPos.setX(colliding_items[i]->pos().x());
            explosionPos.setY(colliding_items[i]->pos().y());

            Explosion* explosion = new Explosion();
            scene()->addItem(explosion);
            explosion->setPos(explosionPos);

            // Remove bullet from scene
            scene()->removeItem(this);
            delete this;

            // Stop checking for collisions with other enemies
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Obstacles)) {
            //disconnect signal from timer
            QPointF explosionPos;
            explosionPos.setX(colliding_items[i]->pos().x());
            explosionPos.setY(colliding_items[i]->pos().y());

            Explosion* explosion = new Explosion();
            scene()->addItem(explosion);
            explosion->setPos(explosionPos);

            // Remove bullet from scene
            scene()->removeItem(colliding_items[i]);

            scene()->removeItem(this);
            delete this;

            // Stop checking for collisions with other enemies
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Shield)) {

            //Enemy* enemy = static_cast<Enemy*>(colliding_items[i]);

            // Reduce enemy's health by bullet's damage
            //enemy->takeDamage(damage);

            QPointF explosionPos;
            explosionPos.setX(colliding_items[i]->pos().x());
            explosionPos.setY(colliding_items[i]->pos().y());

            Explosion* explosion = new Explosion();
            scene()->addItem(explosion);
            explosion->setPos(explosionPos);

            // Remove bullet from scene
            scene()->removeItem(colliding_items[i]);

            scene()->removeItem(this);
            delete this;

            // Stop checking for collisions with other enemies
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Repair)) {

            //Enemy* enemy = static_cast<Enemy*>(colliding_items[i]);

            // Reduce enemy's health by bullet's damage
            //enemy->takeDamage(damage);

            QPointF explosionPos;
            explosionPos.setX(colliding_items[i]->pos().x());
            explosionPos.setY(colliding_items[i]->pos().y());

            Explosion* explosion = new Explosion();
            scene()->addItem(explosion);
            explosion->setPos(explosionPos);

            // Remove bullet from scene
            scene()->removeItem(colliding_items[i]);

            scene()->removeItem(this);
            delete this;

            // Stop checking for collisions with other enemies
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Ammo)) {

        //Enemy* enemy = static_cast<Enemy*>(colliding_items[i]);

        // Reduce enemy's health by bullet's damage
        //enemy->takeDamage(damage);

        QPointF explosionPos;
        explosionPos.setX(colliding_items[i]->pos().x());
        explosionPos.setY(colliding_items[i]->pos().y());

        Explosion* explosion = new Explosion();
        scene()->addItem(explosion);
        explosion->setPos(explosionPos);

        // Remove bullet from scene
        scene()->removeItem(colliding_items[i]);

        scene()->removeItem(this);
        delete this;

        // Stop checking for collisions with other enemies
        return;
        }
    }

    // Move bullet towards the direction of the cursor when it was fired
    setPos(x() + dx, y() + dy);

    // Remove bullet if it goes out of bounds
    if ((pos().y() + boundingRect().height() < 0) || (pos().y() > scene()->height()) || (pos().x() + boundingRect().width() < 0) || (pos().x() > scene()->width())) {
        scene()->removeItem(this);
        //delete timer;
        delete this;
    }
}
