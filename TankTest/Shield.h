
#pragma once
#include<qtimer.h>
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

class Shield : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();

    Q_OBJECT
public:
    Shield(QGraphicsItem* parent = 0);
    //~Shield();
    //QList<QGraphicsItem*> objectDetected();
   

    //char name;

public slots:
    //void spawn();
    

signals:
    

private:

   

    

   

    //void spawn();

};

