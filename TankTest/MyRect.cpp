#include "MyRect.h"
#include <QKeyEvent>
#include "Bullet.h"
#include <QGraphicsScene>
int distance = 5;

void MyRect::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W) {
        if (pos().y() > 0) {

            setPos(x(), y() - distance);
        }
    }
    else if (event->key() == Qt::Key_A) {
        if (pos().x() > 0) {

            setPos(x() - distance, y());
        }
    }
    else if (event->key() == Qt::Key_S) {
        if (pos().y() + distance < scene()->height() - rect().height()) {

            setPos(x(), y() + distance);
        }
    }
    else if (event->key() == Qt::Key_D) {
        if (pos().x() + distance < scene()->width() - rect().width()) {

            setPos(x() + distance, y());
        }
    }
    else if (event->key() == Qt::Key_Space) {
        //Create Bullet
        Bullet* bullet = new Bullet();
        bullet->setPos(x(), y());
        bullet->moveBy(this->boundingRect().width() / 2-7, 0);
        scene()->addItem(bullet);

        
       
    }

}
