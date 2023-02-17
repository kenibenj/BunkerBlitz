#include "wall.h"

Wall::Wall(QObject* parent) :
    QObject(parent), QGraphicsItem()
{

}

Wall::~Wall()
{

}

QRectF Wall::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void Wall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    QImage texture_image(":/images/brick.png");



    painter->drawImage(QRectF(0, 0, 100, 90), texture_image);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}