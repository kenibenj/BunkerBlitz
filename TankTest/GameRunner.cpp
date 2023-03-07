#include "GameRunner.h"
#include "StartMenu.h"
#include "MainHeader.h"
#include "Tank.h"
#include <QPointF>
#include <QHBoxLayout>
#include "HUD.h"
QTimer* enemyTimer = new QTimer();
GameRunner::GameRunner() {
    
    QScreen* primaryScreen = QApplication::primaryScreen();
    QWidget* viewPort = new QWidget();
    viewPort->setFixedSize(1920, 780);
    //viewPort->showFullScreen();
    //Setting up layouts
   // QWidget* window = new QWidget();
    //QHBoxLayout* layout = new QHBoxLayout(window);
    //layout->addWidget(viewPort);
    //Adding HUD object
    //HUD *hud = new HUD();
    //layout->addWidget(hud);
    //layout->setParent(window);
    //layout->
    //Create scene on the heap
    scene = new QGraphicsScene();

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
    view->setGeometry(400, 50, 1920, 780);
    view->setViewport(viewPort);
    QCursor cursor = QCursor(QPixmap(":/images/crosshair.png"));
    view->setCursor(cursor);


    QBrush back_brush(QColor(255, 243, 240)); //bricks & box
    //QBrush back_brush(QColor(224, 255, 224)); //forest

    QPixmap backgroundImage(":/images/bg.png");
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem();
    background->setPixmap(backgroundImage.scaled(scene->width(), scene->height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    background->setZValue(-10);
    scene->addItem(background);


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
    view->centerOn(tank);
    view->show();

    view->setFixedSize(1920, 780);
    viewPort->show();


    tank->setPos(view->width() / 2 - 50, view->height() - 50);
    
    //Adding health HUD

    QPixmap health(":/images/heatlh.png");
    QGraphicsPixmapItem* health1 = new QGraphicsPixmapItem();
    QGraphicsPixmapItem* health2 = new QGraphicsPixmapItem();
    QGraphicsPixmapItem* health3 = new QGraphicsPixmapItem();
    
    health1->setPixmap(health);
    health2->setPixmap(health);
    health3->setPixmap(health);
    
    scene->addItem(health1);
    scene->addItem(health2);
    scene->addItem(health3);

    
    health1->setPos(view->mapToScene(50,50));
    qDebug() << view->mapFromScene(50, 50);
    health2->setPos(view->mapToScene(100, 50));
    health3->setPos(view->mapToScene(150, 50));
    health1->setZValue(10);
    health2->setZValue(10);
    health3->setZValue(10); 
    QObject::connect(enemyTimer, SIGNAL(timeout()), this, SLOT(this.rePositionHUD()));

    health1->show();
    health2->show();
    health3->show();
    


    // spawn enemies
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), tank, SLOT(spawn()));
    timer->start(10000);
    startTimer();
}

// Used when esc key is clicked to pause timers
void GameRunner::pauseTimer() {
    enemyTimer->stop();
}

// Used to start timers
void GameRunner::startTimer() {
    enemyTimer->start(7);
}
void GameRunner::rePositionHUD() {
    qDebug() << "Calling repositioning";
    health1->setPos(view->mapToScene(200, 50));
    health2->setPos(view->mapToScene(100, 50));
    health3->setPos(view->mapToScene(150, 50));
}