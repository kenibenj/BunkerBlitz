#include "Boss.h"
#include "Bullet.h"
#include "Tank.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsDropShadowEffect>

extern QTimer* enemyTimer;
QRandomGenerator Boss::generator = QRandomGenerator::securelySeeded();

Boss::Boss(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {

    pathTravelTime = generator.bounded(10, 26) * 144;

    // set random position
    int randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    int randomNumberY = QRandomGenerator::global()->bounded(900, 1800);
    int randomNumberRotation = QRandomGenerator::global()->bounded(0, 360);

    // determines what kind of aggro-behaviour the AI will have
    int whatType = QRandomGenerator::global()->bounded(0, 3);
    switch (whatType) {
    case 0:
        isFleeType = true;
        isHoldType = false;
        isChargeType = false;
        break;
    case 1:
        isFleeType = false;
        isHoldType = true;
        isChargeType = false;
        break;
    case 2:
        isFleeType = false;
        isHoldType = false;
        isChargeType = true;
        break;
    default:
        isFleeType = true;
        isHoldType = false;
        isChargeType = false;
        break;
    }

    health = 180;
    traversalSpeed = .1;
    rotationSpeed = .15;
    turretRotationSpeed = .4;
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

    setPixmap(QPixmap(":/images/bossChassis.png"));
    setTransformOriginPoint(this->boundingRect().width() / 2, this->boundingRect().height() / 2);


    // Create the healthBar item
    healthBar = new QGraphicsRectItem(0, -10, 50, 5, this);
    healthBar->setRect(0, -10, (health / 100.0) * 50, 5);
    healthBar->setBrush(QColor("#ffed81")); // Yellow color of the Boss tank treads
    healthBar->setPen(QPen(Qt::white, .85));
    healthBar->setPos(-25, -15);

    // Create a QGraphicsDropShadowEffect with a white color and blur radius
    QGraphicsDropShadowEffect* glowEffect = new QGraphicsDropShadowEffect();
    glowEffect->setBlurRadius(10);
    glowEffect->setColor(Qt::white);
    glowEffect->setOffset(0, 0);

    // Apply the effect to the healthBar item
    healthBar->setGraphicsEffect(glowEffect);

    bulletHandler = new QMediaPlayer();
    bulletAudioPlayer = new QAudioOutput();
    bulletAudioPlayer->setVolume(.15);
    bulletHandler->setAudioOutput(bulletAudioPlayer);
    bulletHandler->setSource(QUrl("qrc:/sounds/bossShoot.wav"));

    // connect
    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(frame()));

}

void Boss::createVision() {
    // add a circle
    circle->setRect(0, 0, 1000, 1000); // diameter 1000
    circle->setTransformOriginPoint(circle->boundingRect().width() / 2, circle->boundingRect().height() / 2);
    circle->setPos(x() + this->boundingRect().width() / 2 - circle->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - circle->boundingRect().height() / 2); // center the circle on the enemy
    circle->setZValue(-5);
    circle->setVisible(false);
    scene()->addItem(circle);
}

// Creates turret and sets its point of rotation.
void Boss::createTurret(QString str) {
    int rotationPoint = 7; // 7 pixels down the turret is where the hatch on the turret is which is where the rotation point needs to be.
    turret->setPos(x() + this->boundingRect().width() / 2 - turret->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - turret->boundingRect().height() / 2 - 10);
    turret->setPixmap(QPixmap(":/images/bossTurret.png"));
    turret->setTransformOriginPoint(turret->boundingRect().width() / 2, turret->boundingRect().height() / 2 + rotationPoint);
    turret->setZValue(-2);
    turret->setRotation(rotation());
    scene()->addItem(turret);

    fireFlash->setPixmap(QPixmap(":/images/gunFlash.png"));
    fireFlash->setVisible(false);
    fireFlash->setZValue(-2);
    scene()->addItem(fireFlash);
}

void Boss::frame() {
    counter++;
    QPointF currentPos = pos();
    int currentRot = rotation();
    turret->setPos(x() + this->boundingRect().width() / 2 - turret->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - turret->boundingRect().height() / 2 - 7);
    circle->setPos(x() + this->boundingRect().width() / 2 - circle->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - circle->boundingRect().height() / 2);
    float angleTank = (rotation() - 90) * (M_PI / 180);
    float dxTank = calculateAngleCos(traversalSpeed, angleTank);
    float dyTank = calculateAngleSin(traversalSpeed, angleTank);

    if (bulletCoolDownCounter != 0) {
        bulletCoolDownCounter++;
    }
    if (bulletCoolDownCounter == 72) {
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
                    priorityItem = item;
                    seePlayer = true;
                    roam = false;
                    break;
                }
                else if (typeid(*item) == typeid(Boss)) {
                }
                else if (typeid(*item) == typeid(Bullet)) {
                }
                else {
                }
            }
        }
        else {
        }
    }

    if (seePlayer) {
        float angle = (atan2((priorityItem->y() + (priorityItem->boundingRect().height() / 2)) - (y() + (this->boundingRect().height() / 2)), (priorityItem->x() + (priorityItem->boundingRect().width() / 2)) - (x() + (this->boundingRect().width()) / 2)));
        float angleDegrees = angle * (180 / M_PI) + 90;
        float rotationDifference = angleTo360(angleDegrees - turret->rotation());

        if (rotationDifference < 180) {
            turret->setRotation(turret->rotation() + turretRotationSpeed);
        }
        else if (rotationDifference > 180) {
            turret->setRotation(turret->rotation() - turretRotationSpeed);
        }

        // Boss will turn towards player if they don't have hold ground behavior
        if (!isHoldType) {
            float rotationDifferenceChassis = angleTo360(angleDegrees - this->rotation());
            if (rotationDifferenceChassis < 180) {
                setRotation(rotation() + rotationSpeed);
            }
            else if (rotationDifferenceChassis > 180) {
                setRotation(rotation() - rotationSpeed);
            }

            if (isChargeType) {
                setPos(x() + dxTank, y() + dyTank);
            }
            else {
                setPos(x() - .5 * dxTank, y() - .5 * dyTank);
            }
        }


        float turretAngle = (turret->rotation() - 90) * (M_PI / 180);

        if ((abs(angleTo360(angleDegrees - turret->rotation())) / 360) < .02 && (bulletCoolDownCounter == 0)) {
            Bullet* bullet = new Bullet(this, direction, turretAngle);
            bullet->setPos(x() + this->boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
            scene()->addItem(bullet);
            bullet->fireSwivel();
            bulletCoolDownCounter = 1;
            //Fire Bullet sound
            bulletHandler->setPosition(0);
            bulletHandler->play();
        }
    }

    if (roam) {

        // Set new path after old path expires
        if (pathTravelTime < 0 && !isTurning && !isWallTurning) {
            isTurning = true;
            int random = generator.bounded(10, 16);
            if (random % 2 == 0) {
                isTurningLeft = true;
            }
            else {
                isTurningLeft = false;
            }
            pathTravelTime = random * 144;
            pathTurnTime = generator.bounded(90, 200);
        }

        // When it is turning
        else if (isTurning) {
            if (isTurningLeft) {
                if (pathTurnTime > 0) {
                    setRotation(rotation() + rotationSpeed);
                    pathTurnTime--;
                }
                else {
                    isTurning = false;
                }
            }
            else {
                if (pathTurnTime > 0) {
                    setRotation(rotation() - rotationSpeed);
                    pathTurnTime--;
                }
                else {
                    isTurning = false;
                }
            }
        }

        else if (isWallTurning) {
            if (isTurningLeft) {
                if (pathTurnTime > 0) {
                    setRotation(rotation() + rotationSpeed);
                    pathTurnTime--;
                }
                else {
                    isWallTurning = false;
                    isTurning = false;
                    pathTravelTime = generator.bounded(10, 26) * 144;
                }
            }
            else {
                if (pathTurnTime > 0) {
                    setRotation(rotation() - rotationSpeed);
                    pathTurnTime--;
                }
                else {
                    isWallTurning = false;
                    isTurning = false;
                    pathTravelTime = generator.bounded(10, 26) * 144;
                }
            }
        }

        // When it is trying to get away from the wall
        else if (isAgainstWall) {
            if (pathTravelTime > 0) {
                setPos(x() - dxTank, y() - dyTank);
                pathTravelTime--;
            }
            else {
                isAgainstWall = false;
                isWallTurning = true;
                pathTurnTime = generator.bounded(190, 300);
                if (pathTurnTime % 2 == 0) {
                    isTurningLeft = true;
                }
                else {
                    isTurningLeft = false;
                }
            }
        }

        // Normal movement
        else {
            setPos(x() + dxTank, y() + dyTank);
            pathTravelTime--;
        }

        // Checks to see if Tank is going out of bounds
        if ((x() < 0 || (x() + boundingRect().right() > scene()->width()) || (y() < 0) || (y() + boundingRect().bottom() > scene()->height())))
        {
            previousRotation = rotation();
            setPos(x() - dxTank * 2, y() - dyTank * 2);
            setRotation(currentRot);
            isAgainstWall = true;
            isTurning = false;
            pathTravelTime = generator.bounded(1, 4) * 144;
        }

        if (rotation() > turret->rotation()) {
            turret->setRotation(turret->rotation() + turretRotationSpeed);
        }
        else if (rotation() < turret->rotation()) {
            turret->setRotation(turret->rotation() - turretRotationSpeed);
        }
    }
}

void Boss::setHealth(int health) {
    // Set the size of the health bar based on the enemy's health
    healthBar->setRect(0, -10, (health / 100.0) * 50, 5);
}

void Boss::takeDamage(int damage) {
    // Decrease the enemy's health by the specified amount
    health -= damage;

    // Update the health bar
    setHealth(health);
    if (health <= 100 && health > 50) {
        //setPixmap(QPixmap(":/images/redChasis1.png"));

    }
    if (health <= 50) {
        //setPixmap(QPixmap(":/images/redChasis3.png"));

    }
    // Check if the enemy has been defeated
    if (health <= 0) {
        // Remove the enemy from the scene
        scene()->removeItem(this);

        // Delete the enemy object
        this->deleteLater();
    }
}

// Returns list of meaningful objects colliding with this Enemy's vision circle
QList<QGraphicsItem*> Boss::objectDetected() {
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

float Boss::angleTo360(float rotation) {
    while (rotation >= 360.0) {
        rotation -= 360.0;
    }
    while (rotation < 0.0) {
        rotation += 360.0;
    }
    return rotation;
}

float Boss::calculateAngleCos(float speed, float angle) {
    float dx = speed * cos(angle);
    return dx;
}

float Boss::calculateAngleSin(float speed, float angle) {
    float dy = speed * sin(angle);
    return dy;
}

// Deletes vision-circle when enemy is destroyed
Boss::~Boss() {
    delete circle;
    delete turret;
    delete fireFlash;
}
