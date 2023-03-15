#include "GameRunner.h"
#include "StartMenu.h"
#include "MainHeader.h"
#include "Tank.h"
#include <QPointF>
#include <QHBoxLayout>
#include "Spawner.h"

QTimer* enemyTimer = new QTimer();
GameRunner::GameRunner() {
    startTimer();
    QScreen* primaryScreen = QApplication::primaryScreen();

    //Create scene on the heap
    scene = new QGraphicsScene();

    Spawner spawner(scene);
    //spawner.spawnimage()

    //Set the icon to the GameRunner Window as well
    QGuiApplication::setWindowIcon(QIcon::fromTheme("myicon", QIcon("myicon.png")));

    //add a view, this is what displays the graphics
    view = new QGraphicsView(scene);

    //Add title to the view
    view->setWindowTitle("Bunker Blitz");

    //Create Player's Tank
    Tank* tank = new Tank(view);

    scene->addItem(tank);
    scene->setSceneRect(0, 0, 2400, 1800);

    view->setScene(scene);
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
    tank->createTurret();
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

    tank->setPos(view->width() / 2 - 50, view->height() - 50);
    
    // spawn enemies
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), tank, SLOT(spawn()));
    timer->start(10000);


}

// Used when esc key is clicked to pause timers
void GameRunner::pauseTimer() {
    qDebug() << "Timer paused";
    enemyTimer->stop();
}

// Used to start timers
void GameRunner::startTimer() {
    qDebug() << "Starting Timer";
    enemyTimer->start(7);
}
