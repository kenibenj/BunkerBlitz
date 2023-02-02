#pragma once

#include <QGraphicsPixmapItem>

class Tank :public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tank(QGraphicsItem* parent = 0);
    void keyPressEvent(QKeyEvent* event);

public slots:
    void spawn();
};


