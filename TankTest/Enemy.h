#pragma once

#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QRandomGenerator>
#include <QGraphicsRectItem>

class Enemy : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();

    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = 0);
    ~Enemy();
    QList<QGraphicsItem*> objectDetected();
    void createVision();
    void createTurret();
    float calculateAngleCos(float speed, float angle);
    float calculateAngleSin(float speed, float angle);
    void setHealth(int health);
    void takeDamage(int damage);
public slots:
    void frame();
private:
    float traversalSpeed;
    float rotationSpeed;
    float turretRotationSpeed;

    char direction;

    int health;
    int bulletCoolDownCounter;
    int counter;
    int treadCounter;
    int pathTravelTime;
    int previousRotation;

    bool changeTreads;
    bool roam;
    bool seePlayer;
    bool isAgainstWall;
    bool isTurning;
    bool isTurningLeft;

    QGraphicsEllipseItem* circle;
    QList<QGraphicsItem*> collidingItemsVision;

    static QRandomGenerator generator;

    QGraphicsItem* priorityItem;

    QGraphicsPixmapItem* turret;
    QGraphicsPixmapItem* fireFlash;

    QGraphicsRectItem* healthBar; //declaring health bar for enemy
};
