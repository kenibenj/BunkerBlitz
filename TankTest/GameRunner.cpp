#include "GameRunner.h"
#include "StartMenu.h"
#include "MainHeader.h"
#include "Tank.h"


QTimer* enemyTimer = new QTimer();
GameRunner::GameRunner() {
    startTimer();
    QScreen* primaryScreen = QApplication::primaryScreen();

    //Create scene on the heap
    QGraphicsScene* scene = new QGraphicsScene();

    //add a view, this is what displays the graphics
    QGraphicsView* view = new QGraphicsView(scene);

    //Create rectangle for scene
    //MyRect* player = new MyRect();
    Tank* tank = new Tank(view);

    scene->addItem(tank);
    scene->setSceneRect(0, 0, 1200, 900);

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
// Used when esc key is clicked to pause timers
void GameRunner::pauseTimer() {
    enemyTimer->stop();
}
// Used to start timers
void GameRunner::startTimer() {
    enemyTimer->start(17);
}