#include "Tank.h"
#include "MyRect.h"
#include <QKeyEvent>
#include "Bullet.h"
#include <QGraphicsScene>
#include <Enemy.h>
int Distance = 20;

Tank::Tank()
{
    qDebug() << "Pixmap called";
}

void Tank::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W) {
        if (pos().y() > 0) {

            setPos(x(), y() - Distance);
        }
    }
    else if (event->key() == Qt::Key_A) {
        if (pos().x() > 0) {

            setPos(x() - Distance, y());
        }
    }
    else if (event->key() == Qt::Key_S) {
        if (pos().y() + Distance < scene()->height() - boundingRect().height()) {

            setPos(x(), y() + Distance);
        }
    }
    else if (event->key() == Qt::Key_D) {
        if (pos().x() + Distance < scene()->width() - boundingRect().width()) {

            setPos(x() + Distance, y());
        }
    }
    else if (event->key() == Qt::Key_Space) {
        //Create Bullet
        Bullet* bullet = new Bullet();
        bullet->setPos(x(), y());
        //7 is 1/2 width of bullet
        bullet->moveBy(this->boundingRect().width() / 2 - 7, 0);
        scene()->addItem(bullet);

    }
}
void Tank::spawn() {
    // create an enemy
    Enemy* enemy = new Enemy();
    enemy->setRect(0, 0, 70, 40);
    scene()->addItem(enemy);
}

