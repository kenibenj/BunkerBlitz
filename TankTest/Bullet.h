#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Bullet : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();
    //connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    //timer->start(7);
    Q_OBJECT;
public:
    Bullet(QGraphicsItem* parent = 0);
public slots:
    void move();

};
