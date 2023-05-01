#include "Obstacles.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int

#include <QDebug>



Obstacles::Obstacles(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {

    //isPauseActive = false;
    //v = view;
    //this->setFocus();
    // set random position
    //int randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    //int randomNumberY = QRandomGenerator::global()->bounded(900, 1800);
    //int randomNumberRotation = QRandomGenerator::global()->bounded(0, 360);

    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);
    //setPos(randomNumberX, randomNumberY);
    setZValue(-3);

    setPixmap(QPixmap(":/images/obs.png"));
    setTransformOriginPoint(this->boundingRect().width() / 2, this->boundingRect().height() / 2);





    //connect(enemyTimer, SIGNAL(timeout()), this, SLOT(frame()));
    this->setZValue(-3);
}
//void Shield::spawn() {
    // create an enemy
 //   Shield* shield = new Shield();
 //   scene()->addItem(shield);
    //Obstacles* obstacle = new Obstacles();
    //scene()->addItem(obstacle);
//}
