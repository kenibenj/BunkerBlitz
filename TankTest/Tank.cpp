#include "Tank.h"
#include <QKeyEvent>
#include "Bullet.h"
#include <QGraphicsScene>
#include "Enemy.h"
#include "GameRunner.h"
#include "Explosion.h"
#include "PauseMenu.h"
#include "Obstacles.h"
#include <QGraphicsBlurEffect>  
#include "GameOver.h"
#include <Ammo.h>
#include <Shield.h>
#include <Repair.h>
#include "Boss.h"


extern QTimer* enemyTimer;
Tank::Tank(QGraphicsView* view, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    QTimer* shieldTimer;
    isPauseActive = false;
    v = view;
    this->setFocus();
    turret = new QGraphicsPixmapItem();
    fireFlash = new QGraphicsPixmapItem();

    // Create the healthBar item
    health = 150;

    // Fade
    fadeScreen = new QGraphicsRectItem(0, 0, 3000, 3000);
    fadeScreen->setBrush(QColor("#000000"));
    fadeScreen->setZValue(20);

    //Initialize bullet counter
    bulletCounter = 7;

    //Sets up Key Map
    keys.insert(Qt::Key_W, false);
    keys.insert(Qt::Key_A, false);
    keys.insert(Qt::Key_S, false);
    keys.insert(Qt::Key_D, false);
    keys.insert(Qt::Key_Space, false);
    keys.insert(Qt::Key_Escape, false);

    graphicString = "greenChassisNoDamage";
    setPixmap(QPixmap(":/images/greenChasis.png"));
    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);

    traversalSpeed = .3;
    rotationSpeed = .3;
    direction = 'w';
    counter = 0;
    changeTreads = false;
    isDestroyed = false;
    
    bulletHandler = new QMediaPlayer();
    movingHandler = new QMediaPlayer();
    idleHandler = new QMediaPlayer();
    bulletAudioPlayer = new QAudioOutput();
    movingAudioPlayer = new QAudioOutput();
    idleAudioPlayer = new QAudioOutput();

    fireRateTimer = new QTimer();
    fireRateTimer->setInterval(2000);
    fireRateTimer->setSingleShot(true);

    blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(1);

    bulletAudioPlayer->setVolume(.3);
    movingAudioPlayer->setVolume(.1);
    idleAudioPlayer->setVolume(.1);

    bulletHandler->setAudioOutput(bulletAudioPlayer);
    bulletHandler->setSource(QUrl("qrc:/sounds/bulletFireThree.wav"));

    movingHandler->setAudioOutput(movingAudioPlayer);
    movingHandler->setSource(QUrl("qrc:/sounds/engineMovingThree.wav"));

    idleHandler->setAudioOutput(idleAudioPlayer);
    idleHandler->setSource(QUrl("qrc:/sounds/engineIdleThree.wav"));

    idleHandler->setLoops(QMediaPlayer::Infinite);
    idleHandler->play();

    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(frame()));
    this->setZValue(-3);
}


// Creates turret and sets its point of rotation.
void Tank::createTurret(QString str) {
    int rotationPoint = 7; // 7 pixels down the turret is where the hatch on the turret is which is where the rotation point needs to be.
    turret->setPos(x() + this->boundingRect().width() / 2 - turret->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - turret->boundingRect().height() / 2 - 10);
    turret->setPixmap(QPixmap(str));
    turret->setTransformOriginPoint(turret->boundingRect().width() / 2, turret->boundingRect().height() / 2 + rotationPoint);
    scene()->addItem(turret);

    fireFlash->setPixmap(QPixmap(":/images/gunFlash.png"));
    fireFlash->setVisible(false);
    fireFlash->setZValue(-2);
    scene()->addItem(fireFlash);
}

void Tank::createHUD() {
    healthBarDepleted = new QGraphicsRectItem(20, 20, (health / 100.0) * 145, 17);
    scene()->addItem(healthBarDepleted);
    healthBarDepleted->setBrush(QColor("#90EE90"));
    healthBarDepleted->setPen(QPen(Qt::white, 1));
    healthBarDepleted->setPos(v->mapToScene(10, 10));
    healthBarDepleted->setOpacity(.3);

    healthBar = new QGraphicsRectItem(20, 20, (health / 100.0) * 145, 17);
    scene()->addItem(healthBar);
    healthBar->setBrush(QColor("#90EE90"));
    healthBar->setPen(QPen(Qt::white, 1));
    healthBar->setPos(v->mapToScene(10, 10));

    QGraphicsDropShadowEffect* glowEffect = new QGraphicsDropShadowEffect();
    glowEffect->setBlurRadius(16);
    glowEffect->setColor(Qt::white);
    glowEffect->setOffset(0, 0);

    // Apply the effect to the healthBar item
    healthBar->setGraphicsEffect(glowEffect);

    for (int i = 0; i < bulletCounter; i++) {
        QGraphicsPixmapItem* bullet = new QGraphicsPixmapItem(QPixmap(":/images/bulletGreenHUD.png"));
        scene()->addItem(bullet);
        bullet->setPos(i * bullet->boundingRect().width() + 35, 70);
        bullet->setScale(.55);
        bulletList.append(bullet);
    }
}

void Tank::keyPressEvent(QKeyEvent* event)
{
    keys[event->key()] = true;
    emit positionChanged();
    //Pause menu implementation
    if (event->key() == Qt::Key_Escape) {
        if (pause.isHidden()) {
            GameRunner::pauseTimer();
            pause.setWindowFlag(Qt::WindowStaysOnTopHint);
            pause.setWindowFlag(Qt::FramelessWindowHint);

            pause.show();
        }
    }
}



void Tank::keyReleaseEvent(QKeyEvent* event) {
    keys[event->key()] = false;
}

void Tank::focusOutEvent(QFocusEvent* event)
{
    this->setFocus();
}

float Tank::calculateAngleCos(float speed, float angle) {
    float dx = speed * cos(angle);
    return dx;
}

float Tank::calculateAngleSin(float speed, float angle) {
    float dy = speed * sin(angle);
    return dy;
}

void Tank::frame() {
    if (!isDestroyed) {
        if (fadeScreen->opacity() > 0) {
            fadeScreen->setOpacity(fadeScreen->opacity() - .01);
        }
        currentPos = pos();
        int currentRot = rotation();

        // this code is what lets the tank turret, the muzzle flash, and the bullets follow the cursor. 
        // Every time the frame() function is called (about 144 times per second) the angle from the cursor to the center of the tank is calculated.
        // The function declared variables below will be deleted when the function exits so I do not believe they will cause memory issues
        turret->setPos(x() + this->boundingRect().width() / 2 - turret->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - turret->boundingRect().height() / 2 - 7);

        //Set HUD Position to update every frame

        healthBar->setPos(v->mapToScene(10, 10));
        healthBarDepleted->setPos(v->mapToScene(10, 10));

        int i = 0;
        foreach(QGraphicsPixmapItem * item, bulletList) {
            item->setPos(v->mapToScene(i * item->boundingRect().width() + 35, 70));
            i++;
        }

        QPointF cursorPos = QCursor::pos();
        QPointF cursorViewPos = v->mapFromGlobal(cursorPos);
        QPointF tankPos = this->pos();
        QPointF tankViewPos = v->mapFromScene(tankPos);

        float angle = (atan2(cursorViewPos.y() - (tankViewPos.y() + (this->boundingRect().height() / 2)), cursorViewPos.x() - (tankViewPos.x() + (this->boundingRect().width()) / 2)));
        float angleDegrees = angle * (180 / M_PI);
        turret->setRotation(angleDegrees + 90);

        // Calculate x and y velocity for tank gun muzzle flash
        int dxMuzzleFlash = calculateAngleCos(50, angle);
        int dyMuzzleFlash = calculateAngleSin(50, angle);


        fireFlash->setPos(x() + this->boundingRect().width() / 2 - fireFlash->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - fireFlash->boundingRect().height() / 2);
        fireFlash->moveBy(dxMuzzleFlash, dyMuzzleFlash);
        fireFlash->setTransformOriginPoint(fireFlash->boundingRect().width() / 2, fireFlash->boundingRect().height() / 2);
        fireFlash->setRotation(angleDegrees + 90);


        //Makes view camera follow the tank
        v->centerOn(this);

        // Checking to see how the moving sound should be handled
        if ((isMoving() == true) && (movingHandler->playbackState() != QMediaPlayer::PlayingState)) {
            movingHandler->setPosition(0);
            movingHandler->play();
        }
        else if ((isMoving() == false) && (movingHandler->playbackState() == QMediaPlayer::PlayingState)) {
            movingHandler->setPosition(0);
            movingHandler->stop();
        }

        // Code that handles the animation for the tank treads. Every 20 times the move() function is called while the tank is actually moving
        if ((isMoving() == true)) {
            counter++;
            if (counter % 20 == 0) {
                if (changeTreads == true) {
                    setPixmap(QPixmap(":/images/" + graphicString + "One.png"));
                    changeTreads = false;
                }
                else {
                    setPixmap(QPixmap(":/images/" + graphicString + "Two.png"));
                   changeTreads = true;
                }
            }
        }
        if (health > 100) {
            graphicString = "greenChassisNoDamage";

        }
        if (health <= 100 && health > 50) {
            graphicString = "greenChassisDamagedHalf";


        }
        if (health <= 50) {
            graphicString = "greenChassisDamagedFull";

        }
        if (health >= 500) {
            setPixmap(QPixmap(":/images/blueChasis.png"));

        }
        // Movement & Shooting:

        float angleTank = (rotation() - 90) * (M_PI / 180);
        float dxTank = calculateAngleCos(traversalSpeed, angleTank);
        float dyTank = calculateAngleSin(traversalSpeed, angleTank);

        // traverse
        if (keys[Qt::Key_W]) {
            setPos(x() + dxTank, y() + dyTank);
            direction = 'w';
        }

        // rotate left
        if (keys[Qt::Key_A]) {
            setRotation(rotation() - rotationSpeed);
            direction = 'a';
        }

        // reverse
        if (keys[Qt::Key_S]) {
            setPos(x() - dxTank, y() - dyTank);
            direction = 's';
        }

        // rotate right
        if (keys[Qt::Key_D]) {
            setRotation(rotation() + rotationSpeed);
            direction = 'd';
        }

        // Shooting (Spacebar)
        if (keys[Qt::Key_Space]) {
            if (!fireRateTimer->isActive() && bulletCounter > 0) {
                fireFlash->setVisible(true);

                Bullet* bullet = new Bullet(this, direction, angle);
                bullet->setPos(x() + this->boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y() + this->boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
                scene()->addItem(bullet);

                bullet->fireSwivel();

                //Fire Bullet sound
                bulletHandler->setPosition(0);
                bulletHandler->play();
                // Decrement the bullet counter
                bulletCounter--;

                // Start the fireRateTimer
                fireRateTimer->start();

                for (int i = bulletList.size() - 1; i >= 0; --i) {
                    if (bulletList[i]->opacity() == 1.0) { // if the bullet has an opacity of 100
                        bulletList[i]->setOpacity(0.5);    // set its opacity to 0.5
                        break;                      // break out of the loop
                    }
                }
            }
        }

        if (fireRateTimer->isActive()) {

            // Sets how long the muzzle flush graphic lasts after a shot
            if (fireRateTimer->remainingTime() / (float)fireRateTimer->interval() < .95) {
                fireFlash->setVisible(false);
            }

            // Sets times intervals for dynamic crosshair graphics
            if (fireRateTimer->remainingTime() / (float)fireRateTimer->interval() > .8) {
                QCursor cursor = QCursor(QPixmap(":/images/greenCrosshairGearZero.png"));
                v->setCursor(cursor);
            }
            else if (fireRateTimer->remainingTime() / (float)fireRateTimer->interval() > .6) {
                QCursor cursor = QCursor(QPixmap(":/images/greenCrosshairGearOne.png"));
                v->setCursor(cursor);
            }
            else if (fireRateTimer->remainingTime() / (float)fireRateTimer->interval() > .4) {
                QCursor cursor = QCursor(QPixmap(":/images/greenCrosshairGearTwo.png"));
                v->setCursor(cursor);
            }
            else if (fireRateTimer->remainingTime() / (float)fireRateTimer->interval() > .2) {
                QCursor cursor = QCursor(QPixmap(":/images/greenCrosshairGearThree.png"));
                v->setCursor(cursor);
            }
            else {
                QCursor cursor = QCursor(QPixmap(":/images/greenCrosshairGearFour.png"));
                v->setCursor(cursor);
            }
        }
        else {
            QCursor cursor = QCursor(QPixmap(":/images/crosshair.png"));
            v->setCursor(cursor);
        }

        // Checks to see if Tank is going out of bounds
        if ((x() < 0 || (x() + boundingRect().right() > scene()->width()) || (y() < 0) || (y() + boundingRect().bottom() > scene()->height())))
        {
            setRotation(currentRot);
            setPos(currentPos);
        }

        //Collison check for enemies
        QList<QGraphicsItem*> colliding_items = collidingItems();

        // Iterates through detected objects
        for (int i = 0, n = colliding_items.size(); i < n; i++) {
            if (typeid(*(colliding_items[i])) == typeid(Enemy)) {

                Enemy* enemy = static_cast<Enemy*>(colliding_items[i]);
                QPointF explosionPos;
                explosionPos.setX(colliding_items[i]->pos().x());
                explosionPos.setY(colliding_items[i]->pos().y());

                Explosion* explosion = new Explosion();
                scene()->addItem(explosion);
                explosion->setPos(explosionPos);


                // Reduce enemy's health by bullet's damage
                enemy->takeDamage(50);

                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(Obstacles)) {
                //disconnect signal from timer
                disconnect(enemyTimer, SIGNAL(timeout()), this, SLOT(move()));
                enemyTimer->stop();

                //delete bullet and wall
                scene()->removeItem(colliding_items[i]);
                //scene()->removeItem(this);

                //Delete objects
                //delete(colliding_items[i]);
                //delete(this);
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(Shield)) {

                //Enemy* enemy = static_cast<Enemy*>(colliding_items[i]);

                // Reduce enemy's health by bullet's damage
                //enemy->takeDamage(damage);

                QPointF explosionPos;
                explosionPos.setX(colliding_items[i]->pos().x());
                explosionPos.setY(colliding_items[i]->pos().y());

                Explosion* explosion = new Explosion();
                scene()->addItem(explosion);
                explosion->setPos(explosionPos);
               // setPixmap(QPixmap(":/images/FriendTank1.png"));

                // Remove bullet from scene
                scene()->removeItem(colliding_items[i]);
                health += 500;
                Tank::createTurret(":/images/blueTurret.png");
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(Repair)) {

                //Enemy* enemy = static_cast<Enemy*>(colliding_items[i]);

                // Reduce enemy's health by bullet's damage
                //enemy->takeDamage(damage);

                QPointF explosionPos;
                explosionPos.setX(colliding_items[i]->pos().x());
                explosionPos.setY(colliding_items[i]->pos().y());

                Explosion* explosion = new Explosion();
                scene()->addItem(explosion);
                explosion->setPos(explosionPos);

                // Remove bullet from scene
                scene()->removeItem(colliding_items[i]);
                if (health < 150){
                    //health += 50;
                    takeDamage(-50);
                }
               
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(Ammo)) {

                QPointF explosionPos;
                explosionPos.setX(colliding_items[i]->pos().x());
                explosionPos.setY(colliding_items[i]->pos().y());

                Explosion* explosion = new Explosion();
                scene()->addItem(explosion);
                explosion->setPos(explosionPos);

                // Remove powerup from scene
                scene()->removeItem(colliding_items[i]);

                bulletCounter=7;
                for (int i = 0; i <= bulletList.size() - 1; ++i) {
                        if (bulletList[i]->opacity() == 0.5) { // if the bullet has an opacity of 100
                            bulletList[i]->setOpacity(1);    // set its opacity to 0.5
                        }
                    
                }
                
                return;
            }
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

void Tank::takeDamage(int damage) {
    health = health - damage;
    healthBar->setRect(20, 20, (health / 100.0) * 145, 17);
    // Iterate through the Healthlist in reverse order
    for (int i = healthList.size() - 1; i >= 0; i--) {
        QGraphicsItem* item = healthList.at(i);
        if (item->isVisible()) {
            item->setVisible(false);
            break;  // Stop iterating once we have hidden the last visible item
        }
    }

    // Check if the tank has been defeated
    if (health <= 0) {

        // Remove the enemy from the scene
        isDestroyed = true;
        healthBar->setVisible(false);

        this->setVisible(false);
        turret->setVisible(false);
        movingHandler->stop();
        idleHandler->stop();

        // set the blur effect to the view
        v->setGraphicsEffect(blurEffect);

        connect(enemyTimer, SIGNAL(timeout()), this, SLOT(blur()));
        counter = 0;
        GameOver * gameOver = new GameOver();
        gameOver->show();
    }
}

void Tank::blur() {
    if (counter > 22 && counter % 1 == 0 && blurEffect->blurRadius() < 7) {
        blurEffect->setBlurRadius(blurEffect->blurRadius() + .4);
    }
    counter++;
}


void Tank::spawn() {
    int randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    int randomNumberY = QRandomGenerator::global()->bounded(900, 1800);
    int randomNumberRotation = QRandomGenerator::global()->bounded(0, 360);
    while (randomNumberX <= currentPos.x() - 10 && randomNumberX >= currentPos.x() + 10 ){
        randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    }
    while (randomNumberY <= currentPos.y() - 10 && randomNumberY >= currentPos.y() + 10){
        randomNumberY = QRandomGenerator::global()->bounded(0, 2400);
    }

    // create an enemy
    Enemy* enemy = new Enemy();
    scene()->addItem(enemy);
    enemy->setPos(randomNumberX, randomNumberY);
    enemy->setRotation(randomNumberRotation);
    enemy->createVision();
    enemy->createTurret(":/images/redTurret.png");


    Boss* boss = new Boss();
    scene()->addItem(boss);
    boss->createVision();
    boss->createTurret(":/images/redTurret.png");

}
//Spawns ammo
void Tank::ammoSpawn(){
    int randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    int randomNumberY = QRandomGenerator::global()->bounded(900, 1800);
    while (randomNumberX <= currentPos.x() - 10 && randomNumberX >= currentPos.x() +10){
        randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    }
    while (randomNumberY <= currentPos.y() - 10 && randomNumberY >= currentPos.y() + 10){
        randomNumberY = QRandomGenerator::global()->bounded(0, 2400);
    }
    Ammo* ammo = new Ammo();
    scene()->addItem(ammo);
    ammo->setPos(randomNumberX, randomNumberY);
}
//Spawns repairs
void Tank::repairSpawn(){
    int randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    int randomNumberY = QRandomGenerator::global()->bounded(900, 1800);
    while (randomNumberX <= currentPos.x() - 10 && randomNumberX >= currentPos.x() + 10){
        randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    }
    while (randomNumberY <= currentPos.y() - 10 && randomNumberY >= currentPos.y() + 10){
        randomNumberY = QRandomGenerator::global()->bounded(0, 2400);
    }
    Repair* repair = new Repair();
    scene()->addItem(repair);
    repair->setPos(randomNumberX, randomNumberY);
}
//Spawns Shield
void Tank::shieldSpawn(){
    int randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    int randomNumberY = QRandomGenerator::global()->bounded(900, 1800);
    while (randomNumberX <= currentPos.x() - 10 && randomNumberX >= currentPos.x() + 10){
        randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    }
    while (randomNumberY <= currentPos.y() - 10 && randomNumberY >= currentPos.y() + 10){
        randomNumberY = QRandomGenerator::global()->bounded(0, 2400);
    }
    Shield* shield = new Shield();
    scene()->addItem(shield);
    shield->setPos(randomNumberX, randomNumberY);
}

