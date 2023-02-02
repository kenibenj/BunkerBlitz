#pragma once

#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();

    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = 0);
public slots:
    void move();
};
