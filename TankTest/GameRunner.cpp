#include "GameRunner.h"
#include "StartMenu.h"
#include "MainHeader.h"
#include "Tank.h"
#include "Enemy.h"
#include <QPointF>
#include <QHBoxLayout>
#include "Spawner.h"
#include <QGraphicsScene>

QTimer* enemyTimer = new QTimer();
QTimer* timer = new QTimer();
GameRunner::GameRunner() {
    startTimer();

    QScreen* primaryScreen = QApplication::primaryScreen();

    //Create scene on the heap
    scene = new QGraphicsScene();

    //Spawner spawner(scene);
    //spawner.spawnimage()

    //Set the icon to the GameRunner Window as well
    QGuiApplication::setWindowIcon(QIcon::fromTheme("myicon", QIcon(":/images/icon.png")));

    //add a view, this is what displays the graphics
    view = new QGraphicsView(scene);
    view->showFullScreen();
    //Add title to the view
    view->setWindowTitle("Bunker Blitz");

    //Create Player's Tank
    Tank* tank = new Tank(view);

    scene->addItem(tank);
    scene->setSceneRect(0, 0, 2400, 1800);

    view->setScene(scene);
    view->setTransform(QTransform().scale(1.4, 1.4));
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setBackgroundBrush(QBrush(Qt::black));
    view->setAlignment(Qt::AlignCenter);
    view->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    view->setRenderHint(QPainter::Antialiasing);
    view->setGeometry(400, 50, 1920, 1080);
    
    QCursor cursor = QCursor(QPixmap(":/images/crosshair.png"));
    view->setCursor(cursor);


    QBrush back_brush(QColor(255, 243, 240)); //bricks & box
    //QBrush back_brush(QColor(224, 255, 224)); //forest

    QPixmap backgroundImage(":/images/map.jpg");
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem();
    background->setPixmap(backgroundImage.scaled(scene->width(), scene->height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    background->setZValue(-10);
    scene->addItem(background);


    //makes focuable
    tank->setFlag(QGraphicsItem::ItemIsFocusable);
    tank->setFocus();
    tank->setPos(view->width() / 2 - 50, view->height() - 50);
    tank->createTurret(":/images/greenTurret.png");
    tank->createHUD();

    //Play music
    QMediaPlayer music;
    QAudioOutput audioPlayer;
    audioPlayer.setVolume(.05);
    music.setAudioOutput(&audioPlayer);
    music.setSource(QUrl("qrc:/sounds/backgroundMusic.mp3"));
    music.play();

    view->centerOn(tank);
    view->show();
    view->setFixedSize(1920, 1080);
    view->showFullScreen();

    tank->setPos(scene->width() / 2 - (tank->boundingRect().width() / 2), scene->height() - 150);
    
    // spawn initial enemies and pickups
    tank->spawn();
    tank->spawn();
    tank->pickupSpawn();
    tank->pickupSpawn();
    tank->pickupSpawn();
    
    for (int i = 0; i < 10; i++) {
        tank->obstacleSpawn();
    }
    //QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), tank, SLOT(pickupSpawn()));



}

// Used when esc key is clicked to pause timers
void GameRunner::pauseTimer() {
    enemyTimer->stop();
    timer->stop();
}

// Used to start timers
void GameRunner::startTimer() {
    enemyTimer->start(7);
    timer->start(10000);
}
void GameRunner::gameOverTimers() {
    timer->stop();
}
