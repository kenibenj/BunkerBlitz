#pragma once
#include <QgraphicsRectItem>
#include <QObject>

class Bullet : public QObject, public QGraphicsRectItem {
    Q_OBJECT;
public:
    Bullet();
public slots:
    void move();

};
