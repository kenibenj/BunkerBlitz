#include "MainHeader.h"
#include "Tank.h"
#include <QGraphicsPixmapItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Create scene on the heap
    QGraphicsScene* scene = new QGraphicsScene();

    //Create rectangle for scene
    //MyRect* player = new MyRect();
    Tank *tank = new Tank();

    //by default l and w of rect is 0 need to change
   // tank->setPixmap(QPixmap("tank1.png"));
   // tank->setPos(70, 40);

    //(0, 0, 70,40);
    //add item to scene
    scene->addItem(tank);

    //add a view, this is what displays the graphics
    QGraphicsView* view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setBackgroundBrush(QBrush(Qt::black));
    //makes focuable
    tank-> setFlag(QGraphicsItem::ItemIsFocusable);
    tank->setFocus();
    //Play music
    QMediaPlayer music;
    QAudioOutput audioPlayer;
    audioPlayer.setVolume(.05);
    music.setAudioOutput(&audioPlayer);
    music.setSource(QUrl("qrc:/sounds/backgroundMusic.mp3"));
    music.play();

    view->show();
    view->setFixedSize(1200, 900);
    scene->setSceneRect(0, 0, 1200, 900);
    
    tank->setPos(view->width() / 2 -50, view->height() - 50);
    // spawn enemies
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), tank, SLOT(spawn()));
    timer->start(2000);

    return a.exec();

}
