#pragma once
#include<QGraphicsRectItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "PauseMenu.h"

class Tank :public QObject, public QGraphicsPixmapItem {

    Q_OBJECT
    PauseMenu pause;
    
public:
    Tank(QGraphicsView* view, QGraphicsItem* parent = 0);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void focusOutEvent(QFocusEvent* event);
    //static void setPauseActive(bool x);
    bool isMoving();
    void createTurret();
    
public slots:
    void spawn();
    void frame();

private:
    QMediaPlayer* bulletHandler;
    QMediaPlayer* movingHandler;
    QMediaPlayer* idleHandler;

    QAudioOutput* bulletAudioPlayer;
    QAudioOutput* movingAudioPlayer;
    QAudioOutput* idleAudioPlayer;

    int distance;
    char direction;
    long counter;
    bool changeTreads;

    QTimer* fireRateTimer;
    QTimer* keyTimer;
    QGraphicsView* v;

    QMap<int, bool> keys;

    QGraphicsPixmapItem* turret;
    bool isPauseActive;
    
};


