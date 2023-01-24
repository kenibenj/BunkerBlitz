#include "MyRect.h"
#include <QKeyEvent>
#include "Bullet.h"
#include <QGraphicsScene>

void MyRect::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W) {
        if (pos().y() >= 0) {
            setPos(x(), y() - 10);
        }
    }
    else if (event->key() == Qt::Key_A) {
        if (pos().x() >= 10) {
            setPos(x() - 10, y());
        }
    }
    else if (event->key() == Qt::Key_S) {
        if (pos().y() <= 670) {
            setPos(x(), y() + 10);
        }
    }
    else if (event->key() == Qt::Key_D) {
        if (pos().x() <= 790) {
            setPos(x() + 10, y());
        }
    }
    else if (event->key() == Qt::Key_Space) {
        //Create Bullet
        Bullet* bullet = new Bullet();
        bullet->setPos(x(), y());
        bullet->moveBy(this->boundingRect().width() / 2-7, 0);
        scene()->addItem(bullet);

        if (bullet->pos().y() < 500) {
            scene()->removeItem(this);
            delete this;
        }
       
    }

}
