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
    Bullet(char direction, QGraphicsItem* parent = 0);
    void fireDirectional();
    void fireSwivel();

public slots:
    void move();

private:
    float dx, dy;
    char direct;
    int speed;
};
