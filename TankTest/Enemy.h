#pragma once


#include <QGraphicsRectItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsRectItem {

    Q_OBJECT
public:
    Enemy();
public slots:
    void move();
};
