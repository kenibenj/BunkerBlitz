#pragma once

#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsRectItem>

class Enemy : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();

    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = 0);
    void setHealth(int health);
    void takeDamage(int damage);
public slots:
    void move();
private:
    int distance;
    int health;
    QGraphicsRectItem* healthBar; //declaring health bar for enemy
};
