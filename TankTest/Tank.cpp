#include "Tank.h"
#include "MyRect.h"
#include <QKeyEvent>
#include "Bullet.h"
#include <QGraphicsScene>
#include <Enemy.h>

Tank::Tank(QGraphicsView* view, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    v = view;

    //Sets up Key Map
    keys.insert(Qt::Key_W, false);
    keys.insert(Qt::Key_A, false);
    keys.insert(Qt::Key_S, false);
    keys.insert(Qt::Key_D, false);
    keys.insert(Qt::Key_Space, false);

    setPixmap(QPixmap(":/images/mainTankNew.png"));
    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);

    distance = 5;
    direction = 'w';
    bulletHandler = new QMediaPlayer();
    movingHandler = new QMediaPlayer();
    idleHandler = new QMediaPlayer();
    bulletAudioPlayer = new QAudioOutput();
    movingAudioPlayer = new QAudioOutput();
    idleAudioPlayer = new QAudioOutput();

    fireRateTimer = new QTimer();
    fireRateTimer->setInterval(2000);
    fireRateTimer->setSingleShot(true);

    keyTimer = new QTimer();

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

    connect(keyTimer, SIGNAL(timeout()), this, SLOT(move()));
    keyTimer->start(17);
}

void Tank::keyPressEvent(QKeyEvent* event)
{
    keys[event->key()] = true;
}

void Tank::keyReleaseEvent(QKeyEvent* event) {
    keys[event->key()] = false;
}

void Tank::focusOutEvent(QFocusEvent* event)
{
    this->setFocus();
}

void Tank::move() {

    //Makes view camera follow the tank
    //v->centerOn(this);

    // Checking to see how the moving sound should be handled
    if ((isMoving() == true) && (movingHandler->playbackState() != QMediaPlayer::PlayingState)) {
        movingHandler->setPosition(0);
        movingHandler->play();
    }
    else if ((isMoving() == false) && (movingHandler->playbackState() == QMediaPlayer::PlayingState)) {
        movingHandler->setPosition(0);
        movingHandler->stop();
    }

    //Movement
    if (keys[Qt::Key_W]) {
        if (pos().y() > 0) {
            setPos(x(), y() - distance);
            setRotation(0); // facing upwards
            direction = 'w';
        }
    }

    else if (keys[Qt::Key_A]) {
        if (pos().x() > 0) {
            setPos(x() - distance, y());
            setRotation(270); // facing left
            direction = 'a';
        }
    }

    else if (keys[Qt::Key_S]) {
        if (pos().y() + distance < scene()->height() - boundingRect().height()) {
            setPos(x(), y() + distance);
            setRotation(180); // facing downwards
            direction = 's';
        }
    }

    else if (keys[Qt::Key_D]) {
        if (pos().x() + distance < scene()->width() - boundingRect().width()) {
            setPos(x() + distance, y());
            setRotation(90); // facing right
            direction = 'd';
        }
    }

    // Shooting (Spacebar)
    if (keys[Qt::Key_Space]) {
        qDebug() << "Shooting";
        if (!fireRateTimer->isActive()) {

            // Get cursor position when bullet is created
            QPoint cursorPos = QCursor::pos();
            QPointF cursorScenePos = v->mapFromGlobal(cursorPos);

            //Create Bullet and gives it the direction the tank is facing(for directional firing) and cursor position (for swivel firing)
            Bullet* bullet = new Bullet(direction, cursorScenePos);
            bullet->setPos(x() + this->boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
            scene()->addItem(bullet);

            //This can be set to either 'fire()' for cursor shooting or 'fireAlt()' for directional shooting
            bullet->fireSwivel();

            //Fire Bullet sound
            bulletHandler->setPosition(0);
            bulletHandler->play();

            // Start the fireRateTimer
            fireRateTimer->start();
        }
    }
}

bool Tank::isMoving() {
    if (keys[Qt::Key_W] || keys[Qt::Key_A] || keys[Qt::Key_S] || keys[Qt::Key_D]) {
        return true;
    }
    else {
        return false;
    }
}

void Tank::spawn() {
    // create an enemy
    Enemy* enemy = new Enemy();
    scene()->addItem(enemy);
}

