#include <Ammo.h>
#include <QRandomGenerator>



Ammo::Ammo(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {

    
    int randomNumberX = QRandomGenerator::global()->bounded(0, 2400);
    int randomNumberY = QRandomGenerator::global()->bounded(900, 1800);
    int randomNumberRotation = QRandomGenerator::global()->bounded(0, 360);

    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);
    setPos(randomNumberX, randomNumberY);
    setZValue(-3);

    setPixmap(QPixmap(":/images/Ammo_Pickup.png"));
    setTransformOriginPoint(this->boundingRect().width() / 2, this->boundingRect().height() / 2);





    this->setZValue(-3);
}

