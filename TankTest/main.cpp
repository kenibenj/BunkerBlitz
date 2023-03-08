#include "MainHeader.h"
#include "Tank.h"
#include "StartMenu.h"
#include <QGraphicsPixmapItem>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartMenu game;
    game.show();

    return a.exec();
}
