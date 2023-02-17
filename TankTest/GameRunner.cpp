#include "GameRunner.h"
#include "StartMenu.h"
#include "MainHeader.h"
#include "Tank.h"
#include "map_creator.h"

QTimer* enemyTimer = new QTimer();
GameRunner::GameRunner() {
    enemyTimer->start(17);
    QScreen* primaryScreen = QApplication::primaryScreen();

    //creates an instance of the MapCreator class and sets the file path for the map file. 
    MapCreator map_creator;
    map_creator.setFile("my_map.txt"); //change the file path if it doesn't work
    //Not sure why qrc path doesn't work

    //Create scene on the heap
    QGraphicsScene* scene = new QGraphicsScene();

    int w = primaryScreen->geometry().width() / 2;
    int h = primaryScreen->geometry().height() / 2;

    //add a view, this is what displays the graphics
    QGraphicsView* view = new QGraphicsView(scene);

    //Create rectangle for scene
    //MyRect* player = new MyRect();
    Tank* tank = new Tank(view);

    scene->addItem(tank);
    scene->setSceneRect(0, 0, 1200, 900);

    //Create map using map_creator
    map_creator.CreateMap(scene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setBackgroundBrush(QBrush(Qt::black));
    view->setAlignment(Qt::AlignCenter);
    view->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    view->setRenderHint(QPainter::Antialiasing);
    view->setGeometry(400, 50, 1200, 900);
    QCursor cursor = QCursor(QPixmap(":/images/crosshair.png"));
    view->setCursor(cursor);


    QBrush back_brush(QColor(255, 243, 240)); //bricks & box
    //QBrush back_brush(QColor(224, 255, 224)); //forest

    scene->setBackgroundBrush(back_brush);


      //makes focuable
    tank->setFlag(QGraphicsItem::ItemIsFocusable);
    tank->setFocus();
    tank->setPos(view->width() / 2 - 50, view->height() - 50);
    tank->createTurret();
    //Play music
    QMediaPlayer music;
    QAudioOutput audioPlayer;
    audioPlayer.setVolume(.05);
    music.setAudioOutput(&audioPlayer);
    music.setSource(QUrl("qrc:/sounds/backgroundMusic.mp3"));
    music.play();

    view->show();
    view->setFixedSize(1200, 900);

    tank->setPos(view->width() / 2 - 50, view->height() - 50);

    // spawn enemies
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), tank, SLOT(spawn()));
    timer->start(10000);
}