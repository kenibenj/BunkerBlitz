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
    void fireDirectional();
    void fireSwivel();

public slots:
    void frame();

private:
    float dx, dy;
    char direct;
    float speed;
    float angle;
    QGraphicsItem* tank;
};
