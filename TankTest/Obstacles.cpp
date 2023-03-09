#include "Obstacles.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int

#include <QDebug>

extern QTimer* enemyTimer;
Obstacles::Obstacles(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem() {
    //set random position
    int random_number = rand() % 700;
    

    setPos(random_number, random_number);

    // drew the rect
   // setRect(0, 0, 100, 100);
    setPixmap(QPixmap(":/images/Ammobox.jpg"));
    

    // connect
    //connect(enemyTimer, SIGNAL(timeout()), this, SLOT(move()));

}




