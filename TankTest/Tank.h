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
    
public slots:
    void spawn();
    void frame();
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

    QTimer* fireRateTimer;
    QTimer* keyTimer;
    QGraphicsView* v;

    QMap<int, bool> keys;

    QGraphicsPixmapItem* turret;
    QGraphicsPixmapItem* fireFlash;
    QGraphicsPixmapItem* bulletHUD;
    QGraphicsTextItem* bulletCounterHUD;
    int bulletCounter;

    
};


