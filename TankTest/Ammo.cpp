#include <Ammo.h>
#include <QRandomGenerator>



Ammo::Ammo(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {

    

    int randomNumberRotation = QRandomGenerator::global()->bounded(0, 360);

    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);
    setZValue(-3);

    setPixmap(QPixmap(":/images/Ammo_Pickup.png"));
    setTransformOriginPoint(this->boundingRect().width() / 2, this->boundingRect().height() / 2);





    this->setZValue(-3);
}

