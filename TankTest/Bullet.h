#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Bullet : public QObject, public QGraphicsRectItem {
    QTimer* timer = new QTimer();
    //connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    //timer->start(7);
    Q_OBJECT;
public:
    Bullet();
public slots:
    void move();

};
