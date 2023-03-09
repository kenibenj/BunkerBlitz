#pragma once

#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QObject>

class Obstacles : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();

    Q_OBJECT
public:
    Obstacles( QGraphicsItem* parent = 0);
public slots:
    //void move();
    //void spawn();
private:
};
