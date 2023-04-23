#pragma once

#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QRandomGenerator>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "tank.h"

class Enemy : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();

    Q_OBJECT
public:
    Enemy(QGraphicsItem* player, QGraphicsItem* parent = 0);
    ~Enemy();
    QList<QGraphicsItem*> objectDetected();
    void createVision();
    void createTurret(QString str);
    void createTurret();
    float calculateAngleCos(float speed, float angle);
    float calculateAngleSin(float speed, float angle);
    void setHealth(int health);
    void takeDamage(int damage);
    float angleTo360(float rotation);
    void setName(char name);

    char name;

public slots:
    void frame();

private:
    Tank* playerTank;

    float traversalSpeed;
    float rotationSpeed;
    float turretRotationSpeed;

    char direction;

    int health;
    int MAXHEALTH;
    int bulletCoolDownCounter;
    int counter;
    int treadCounter;
    int retreatCounter;
    int pathTravelTime;
    int pathTurnTime;
    int previousRotation;

    bool changeTreads;
    bool roam;
    bool seePlayer;
    bool isAgainstWall;
    bool isTurning;
    bool isTurningLeft;
    bool isWallTurning;
    bool isMoving;

    bool isChargeType;
    bool isFleeType;
    bool isHoldType;

    QAudioOutput* bulletAudioPlayer;
    QMediaPlayer* bulletHandler;

    QGraphicsEllipseItem* circle;
    QList<QGraphicsItem*> collidingItemsVision;

    static QRandomGenerator generator;

    QGraphicsItem* priorityItem;

    QGraphicsPixmapItem* turret;
    QGraphicsPixmapItem* fireFlash;

    QString graphicString;

    QGraphicsRectItem* healthBar; //declaring health bar for enemy

};