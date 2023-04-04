#include "Explosion.h"
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QMovie>
#include <QLabel>
#include <QGraphicsItem>

extern QTimer* enemyTimer;
Explosion::Explosion(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)

{
    setPixmap(QPixmap(":/images/explosionOne.png"));

    // set the scale of explosion
    setScale(0.5);

    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(frame()));

    explosionPlayer = new QMediaPlayer();
    explosionOutput = new QAudioOutput();

    explosionOutput->setVolume(.3);

    explosionPlayer->setAudioOutput(explosionOutput);
    explosionPlayer->setSource(QUrl("qrc:/sounds/explosion.wav"));
    explosionPlayer->play();

    counter = 0;
    explosionLength = .1 * 144;
}

void Explosion::frame() {
    if (counter / explosionLength > 1) {
        removeExplosion();
    }
    counter++;
}

// Method to remove the explosion and associated timer
void Explosion::removeExplosion() {
    scene()->removeItem(this);
    delete this;
}