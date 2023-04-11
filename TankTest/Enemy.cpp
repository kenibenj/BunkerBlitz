#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Explosion.h"
#include <QDebug>

extern QTimer *enemyTimer;
Enemy::Enemy(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {
    //set random position
    int random_number = rand() % 700;
    distance = 1;
    setPos(random_number, 0);

    // drew the rect
   // setRect(0, 0, 100, 100);
    setPixmap(QPixmap(":/images/enemyTankNew.png"));
    setTransformOriginPoint(50, 50);
    setRotation(180);

    // Create Health Bar
    health = 100;
    healthBar = new QGraphicsRectItem(0, -10, 50, 5, this);
    healthBar->setBrush(Qt::green);
    healthBar->setPen(Qt::NoPen);
    healthBar->setPos(-25, -15);

    // connect
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(move()));

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

void Enemy::setHealth(int health) {
    // Set the size of the health bar based on the enemy's health
    healthBar->setRect(0, -10, (health / 100.0) * 50, 5);
}

void Enemy::takeDamage(int damage) {
    // Decrease the enemy's health by the specified amount
    health -= damage;

    // Update the health bar
    setHealth(health);

    // Check if the enemy has been defeated
    if (health <= 0) {
        // Remove the enemy from the scene
        scene()->removeItem(this);

        // Delete the enemy object
        this->deleteLater();
    }
}
