#include "Explosion.h"
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QMovie>
#include <QLabel>
#include <qGraphicsItem>

Explosion::Explosion(QPointF position, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)

{
    setPixmap(QPixmap(":/images/explosion.gif"));

    // set the scale of explosion
    setScale(0.5);

    // set the position to the specified position argument
    setPos(position);

    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Explosion::removeExplosion);
    m_timer->start(150);
}

// Method to remove the explosion and associated timer
void Explosion::removeExplosion()
{
    delete m_timer;
    scene()->removeItem(this);
    delete this;
}