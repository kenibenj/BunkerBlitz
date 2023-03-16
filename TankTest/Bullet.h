#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Bullet : public QObject, public QGraphicsPixmapItem {
    QTimer* timer = new QTimer();

    Q_OBJECT;

public:
    Bullet(QGraphicsItem* tank, char direction, float angle, QGraphicsItem* parent = 0);
    void fireSwivel();

public slots:
    void move();

private:
    int damage;
    float dx, dy;
    char direct;
    float speed;
    float angle;
    QGraphicsItem* tank;
};
