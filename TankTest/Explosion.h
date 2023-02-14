#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Explosion(QPointF position, QGraphicsItem* parent = nullptr);

private slots:
    void removeExplosion();

private:
    QTimer* m_timer;
};
