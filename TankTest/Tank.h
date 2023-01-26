#pragma once

#include <QGraphicsPixmapItem>

class Tank :public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tank();
    void keyPressEvent(QKeyEvent* event);

public slots:
    void spawn();
};


