#include "Tank.h"
#include "MyRect.h"
#include <QKeyEvent>
#include "Bullet.h"
#include <QGraphicsScene>
#include <Enemy.h>

Tank::Tank(QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/MainTain.png"));
    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);

    distance = 5;
    direction = 'w';
    bulletHandler = new QMediaPlayer();
    movingHandler = new QMediaPlayer();
    idleHandler = new QMediaPlayer();
    bulletAudioPlayer = new QAudioOutput();
    movingAudioPlayer = new QAudioOutput();
    idleAudioPlayer = new QAudioOutput();
    isMoving = false;

    bulletAudioPlayer->setVolume(1);
    movingAudioPlayer->setVolume(1);
    idleAudioPlayer->setVolume(1);

    bulletHandler->setAudioOutput(bulletAudioPlayer);
    bulletHandler->setSource(QUrl("qrc:/sounds/bullet.mp3"));

    movingHandler->setAudioOutput(movingAudioPlayer);
    movingHandler->setSource(QUrl("qrc:/sounds/tankMoving.mp3"));

    idleHandler->setAudioOutput(idleAudioPlayer);
    idleHandler->setSource(QUrl("qrc:/sounds/tankIdle.mp3"));

    idleHandler->setLoops(QMediaPlayer::Infinite);
    idleHandler->play();
}

void Tank::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W) {
        if (pos().y() > 0) {
            setPos(x(), y() - distance);
            setRotation(0); // facing upwards
            direction = 'w';
        }
        isMoving = true;
        if (movingHandler->playbackState() != QMediaPlayer::PlayingState) {
            movingHandler->setPosition(0);
            movingHandler->play();
        }
    }
    else if (event->key() == Qt::Key_A) {
        if (pos().x() > 0) {
            setPos(x() - distance, y());
            setRotation(270); // facing left
            direction = 'a';
        }
        isMoving = true;
        if (movingHandler->playbackState() != QMediaPlayer::PlayingState) {
            movingHandler->setPosition(0);
            movingHandler->play();
        }
    }
    else if (event->key() == Qt::Key_S) {
        if (pos().y() + distance < scene()->height() - boundingRect().height()) {
            setPos(x(), y() + distance);
            setRotation(180); // facing downwards
            direction = 's';
        }
        isMoving = true;
        if (movingHandler->playbackState() != QMediaPlayer::PlayingState) {
            movingHandler->setPosition(0);
            movingHandler->play();
        }
    }
    else if (event->key() == Qt::Key_D) {
        if (pos().x() + distance < scene()->width() - boundingRect().width()) {
            setPos(x() + distance, y());
            setRotation(90); // facing right
            direction = 'd';
        }
        isMoving = true;
        if (movingHandler->playbackState() != QMediaPlayer::PlayingState) {
            movingHandler->setPosition(0);
            movingHandler->play();
        }
    }
    else if (event->key() == Qt::Key_Space) {

        //Create Bullet
        Bullet* bullet = new Bullet(direction);
        bullet->setPos(x() + this->boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
        scene()->addItem(bullet);

        //This can be set to either 'fire()' for cursor shooting or 'fireAlt()' for directional shooting
        bullet->fireSwivel();

        //Fire Bullet sound
        bulletHandler->setPosition(0);
        bulletHandler->play();
    }
}

void Tank::keyReleaseEvent(QKeyEvent* event) {
    isMoving = false;
}

void Tank::focusOutEvent(QFocusEvent* event)
{
    this->setFocus();
}

void Tank::spawn() {
    // create an enemy
    Enemy* enemy = new Enemy();
    //enemy->setRect(0, 0, 70, 40);
    scene()->addItem(enemy);
}

