#include "MainHeader.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Create scene on the heap
    QGraphicsScene* scene = new QGraphicsScene();

    //Create rectangle for scene
    MyRect* player = new MyRect();

    //by default l and w of rect is 0 need to change
    player->setRect(0, 0, 70,40);
    //add item to scene
    scene->addItem(player);

    //add a view, this is what displays the graphics
    QGraphicsView* view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //makes focuable
    player-> setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
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
    
    player->setPos(view->width() / 2 -50, view->height() - player->rect().height());

    return a.exec();

}
