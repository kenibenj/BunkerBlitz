#pragma once
#include<QGraphicsRectItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "PauseMenu.h"
#include <QPointF>
#include <QLabel>
#include <QGraphicsTextItem>
#include <QGraphicsBlurEffect>
#include <QStack>

class Tank :public QObject, public QGraphicsPixmapItem {

    Q_OBJECT
    PauseMenu pause;
    QGraphicsPixmapItem* health1;
    QGraphicsPixmapItem* health2;
    QGraphicsPixmapItem* health3;
public:
    Tank(QGraphicsView* view, QGraphicsItem* parent = 0);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void focusOutEvent(QFocusEvent* event);
    bool isMoving();
    void createTurret();
    void createHUD();
    float calculateAngleCos(float speed, float angle);
    float calculateAngleSin(float speed, float angle);
    void takeDamage(int damage);
    
public slots:
    void spawn();
    void frame();
    void blur();

signals:
    void positionChanged();

private:
    QMediaPlayer* bulletHandler;
    QMediaPlayer* movingHandler;
    QMediaPlayer* idleHandler;

    QAudioOutput* bulletAudioPlayer;
    QAudioOutput* movingAudioPlayer;
    QAudioOutput* idleAudioPlayer;

    float traversalSpeed;
    float rotationSpeed;
    char direction;
    long counter;

    bool changeTreads;
    bool isPauseActive;
    bool isDestroyed;

    QTimer* fireRateTimer;
    QGraphicsView* v;

    QMap<int, bool> keys;

    QGraphicsPixmapItem* turret;
    QGraphicsPixmapItem* fireFlash;
    QGraphicsPixmapItem* bulletHUD;
    QGraphicsTextItem* bulletCounterHUD;

    int health;
    int bulletCounter;

    QList<QGraphicsItem*> healthList;
    QList<QGraphicsPixmapItem*> bulletList;

    QGraphicsBlurEffect* blurEffect;

    QGraphicsRectItem* healthBar;
    QGraphicsRectItem* healthBarDepleted;
    QGraphicsRectItem* fadeScreen;
};


