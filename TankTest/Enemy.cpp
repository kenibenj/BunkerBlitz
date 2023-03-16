#include "Enemy.h"
#include "Bullet.h"
#include "Tank.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include <QDebug>
#include <QRandomGenerator>

extern QTimer *enemyTimer;
QRandomGenerator Enemy::generator = QRandomGenerator::securelySeeded();

Enemy::Enemy(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {

    pathTravelTime = generator.bounded(10, 26) * 144;


    // set random position
    int randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    int randomNumberY = QRandomGenerator::global()->bounded(900, 1800);
    int randomNumberRotation = QRandomGenerator::global()->bounded(0, 360);
    traversalSpeed = .3;
    rotationSpeed = .3;
    turretRotationSpeed = .2;
    counter = 0;
    treadCounter = 0;
    bulletCoolDownCounter = 0;
    seePlayer = false;
    roam = true;
    isAgainstWall = false;
    circle = new QGraphicsEllipseItem();
    turret = new QGraphicsPixmapItem();
    fireFlash = new QGraphicsPixmapItem();
    direction = 'w';

    setPos(randomNumberX, randomNumberY);
    setRotation(randomNumberRotation);
    setZValue(-3);

    setPixmap(QPixmap(":/images/redChasis.png"));
    setTransformOriginPoint(this->boundingRect().width() / 2, this->boundingRect().height() / 2);

    // connect
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(frame()));
}

void Enemy::createVision() {
    // add a circle
    circle->setRect(0,0, 1000, 1000); // diameter 100
    circle->setTransformOriginPoint(circle->boundingRect().width() / 2, circle->boundingRect().height() / 2);
    circle->setPos(x() + this->boundingRect().width() / 2 - circle->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - circle->boundingRect().height() / 2); // center the circle on the enemy
    circle->setBrush(QBrush(Qt::blue)); // set color and style of the circle's interior\

    circle->setZValue(-5);
    circle->setVisible(false);
    scene()->addItem(circle);
}

// Creates turret and sets its point of rotation.
void Enemy::createTurret() {
    int rotationPoint = 7; // 7 pixels down the turret is where the hatch on the turret is which is where the rotation point needs to be.
    turret->setPos(x() + this->boundingRect().width() / 2 - turret->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - turret->boundingRect().height() / 2 - 10);
    turret->setPixmap(QPixmap(":/images/redTurret.png"));
    turret->setTransformOriginPoint(turret->boundingRect().width() / 2, turret->boundingRect().height() / 2 + rotationPoint);
    turret->setZValue(-2);
    turret->setRotation(rotation());
    scene()->addItem(turret);

    fireFlash->setPixmap(QPixmap(":/images/gunFlash.png"));
    fireFlash->setVisible(false);
    fireFlash->setZValue(-2);
    scene()->addItem(fireFlash);
}


void Enemy::frame() {
    QPointF currentPos = pos();
    turret->setPos(x() + this->boundingRect().width() / 2 - turret->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - turret->boundingRect().height() / 2 - 7);
    circle->setPos(x() + this->boundingRect().width() / 2 - circle->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - circle->boundingRect().height() / 2);
    float angleTank = (rotation() - 90) * (M_PI / 180);
    float dxTank = calculateAngleCos(traversalSpeed, angleTank);
    float dyTank = calculateAngleSin(traversalSpeed, angleTank);
    counter++;

    if (bulletCoolDownCounter != 0) {
        bulletCoolDownCounter++;
    }
    if (bulletCoolDownCounter == 288) {
        bulletCoolDownCounter = 0;
    }


    // Collision detection is computationally expensive - will slow down program if ran too many times per second.
    // As a result I have set it so it will only run once a second.
    if (counter % 144 == 0) {
        QList<QGraphicsItem*> collidingItemsVision = objectDetected();
        roam = true;
        seePlayer = false;
        if (!collidingItemsVision.isEmpty()) {
            for (QGraphicsItem* item : collidingItemsVision) {
                if (typeid(*item) == typeid(Tank)) {
                    qDebug() << "Player!" << item->zValue();
                    priorityItem = item;
                    seePlayer = true;
                    roam = false;
                }
                else if (typeid(*item) == typeid(Enemy)) {
                    qDebug() << "Enemy!" << item->zValue();
                }
                else if (typeid(*item) == typeid(Bullet)) {
                    qDebug() << "Bullet!" << item->zValue();
                }
                else {
                    qDebug() << "wtf!" << item->zValue();
                }
            }
        }
        else {
        }
    }

    if (counter % pathTravelTime == 0 || (isAgainstWall && !isTurning)) {
        isTurning = true;
        int random = generator.bounded(10, 26);
        if (random % 2 == 0) {
            isTurningLeft = true;
        }
        else {
            isTurningLeft = false;
        }
        pathTravelTime = random * 144;
        previousRotation = rotation();
    }


    if (seePlayer) {
        float angle = (atan2((priorityItem->y() + (priorityItem->boundingRect().height() / 2))- (y() + (this->boundingRect().height() / 2)), (priorityItem->x() + (priorityItem->boundingRect().width() / 2)) - (x() + (this->boundingRect().width()) / 2)));
        float angleDegrees = angle * (180 / M_PI) + 90;

        if (angleDegrees > turret->rotation()) {
            turret->setRotation(turret->rotation() + turretRotationSpeed);
        }
        else if (angleDegrees < turret->rotation()) {
            turret->setRotation(turret->rotation() - turretRotationSpeed);
        }

        float turretAngle = (turret->rotation() - 90) * (M_PI / 180);

        if ( (abs(angleDegrees - turret->rotation()) / 360) < .05 && (bulletCoolDownCounter == 0 )) {
            Bullet* bullet = new Bullet(this, direction, turretAngle);
            bullet->setPos(x() + this->boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
            scene()->addItem(bullet);

            //This can be set to either 'fire()' for cursor shooting or 'fireAlt()' for directional shooting
            bullet->fireSwivel();

            bulletCoolDownCounter = 1;
        }
    }

    if (roam) {
        if (isTurning && !isAgainstWall) {
            if (isTurningLeft) {
                if (rotation() < previousRotation + generator.bounded(40, 90)) {
                    setRotation(rotation() + rotationSpeed);
                }
                else {
                    isTurning = false;
                }
            }
            else {
                if (rotation() > previousRotation - generator.bounded(40, 90)) {
                    setRotation(rotation() - rotationSpeed);
                }
                else {
                    isTurning = false;
                }
            }
        }

        else if (isTurning || isAgainstWall) {
            if (rotation() > previousRotation - 180) {
                setRotation(rotation() - rotationSpeed);
            }
            else {
                isTurning = false;
                isAgainstWall = false;
            }
        }

        else if (!isTurning) {
            setPos(x() + dxTank, y() + dyTank);

            // Checks to see if Tank is going out of bounds
            if (x() < 0)
            {
                setPos(currentPos);
                isAgainstWall = true;
            }
            else if (x() + boundingRect().right() > scene()->width())
            {
                setPos(currentPos);
                isAgainstWall = true;
            }

            if (y() < 0)
            {
                setPos(currentPos);
                isAgainstWall = true;
            }
            else if (y() + boundingRect().bottom() > scene()->height())
            {
                setPos(currentPos);
                isAgainstWall = true;
            }
        }

        if (rotation() > turret->rotation()) {
            turret->setRotation(turret->rotation() + turretRotationSpeed);
        }
        else if (rotation() < turret->rotation()) {
            turret->setRotation(turret->rotation() - turretRotationSpeed);
        }
    }
}

// Returns list of meaningful objects colliding with this Enemy's vision circle
QList<QGraphicsItem*> Enemy::objectDetected() {
    QList<QGraphicsItem*> collidingItemsVision = circle->collidingItems();

    // Removes its own Tank graphic from list
    collidingItemsVision.removeOne(this);

    // Removes graphic items with Z-values of -10(background), -5(other vision circles), and -2(tank turrets and muzzle flashes)
    for (int i = 0; i < collidingItemsVision.size(); i++) {
        QGraphicsItem* item = collidingItemsVision[i];
        if (item->zValue() == -10 || item->zValue() == -5 || item->zValue() == -2) {
            collidingItemsVision.removeOne(item);
            i--;
        }
        else {
        }
    }
    return collidingItemsVision;
}

float Enemy::calculateAngleCos(float speed, float angle) {
    float dx = speed * cos(angle);
    return dx;
}

float Enemy::calculateAngleSin(float speed, float angle) {
    float dy = speed * sin(angle);
    return dy;
}

// Deletes vision-circle when enemy is destroyed
Enemy::~Enemy() {
    delete circle;
    delete turret;
    delete fireFlash;
}
