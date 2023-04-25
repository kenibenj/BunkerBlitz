#pragma once

#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QRandomGenerator>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Tank.h"

class Boss : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();

    Q_OBJECT
public:
    Boss(QGraphicsItem* player, QGraphicsItem* parent = 0);
    ~Boss();
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

    bool isChargeType;
    bool isFleeType;
    bool isHoldType;

    QGraphicsEllipseItem* circle;
    QList<QGraphicsItem*> collidingItemsVision;

    static QRandomGenerator generator;

    QGraphicsItem* priorityItem;

    QGraphicsPixmapItem* turret;
    QGraphicsPixmapItem* fireFlash;

    QAudioOutput* bulletAudioPlayer;
    QMediaPlayer* bulletHandler;

    QGraphicsRectItem* healthBar; //declaring health bar for Boss

};
