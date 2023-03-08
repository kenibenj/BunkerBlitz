#include "StartMenu.h"
#include "MainHeader.h"
#include "Tank.h"
#include "GameRunner.h"
#include <QWindow>

StartMenu::StartMenu(QWidget* parent) : QWidget{parent}
{
    setFixedSize(1920, 1080);
    showFullScreen();
    //Title for the window
    setWindowTitle("Bunker Blitz");

    //Set the icon to the window
    setWindowIcon(QIcon::fromTheme("myicon", QIcon("myicon.png")));

    //Setting color palette
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);

    //Allows window to be set to a color
    setAutoFillBackground(true);
    //Sets the color of the window
    setPalette(pal);


    int startButtonHeight = 120;
    int startButtonWidth = 250;
    int quitButtonHeight = 90;
    int quitButtonWidth = 150;
    QPushButton* startButton = new QPushButton("Start", this);
    QPushButton* quitButton = new QPushButton("Quit", this);
    startButton->setGeometry(width() / 2 - (startButtonWidth / 2), height() / 2 - (startButtonHeight / 2), 250, 120); // 125
    quitButton->setGeometry(width() / 2 - (quitButtonWidth / 2), (height() / 2) + (quitButtonHeight), 150, 90);


    //Adjusting style for the buttons
    startButton->setStyleSheet("color: black; background-color: lightGreen; border-style: outset; border-width: 3px; border-color: darkGreen; font: 30px");
    quitButton->setStyleSheet("color: black; background-color: lightGreen; border-style: outset; border-width: 3px; border-color: darkGreen; font: 20px");
    
    //Adding in title 
    
    //title.setPos(100, 100);
    //title.setPixmap(QPixmap());
    //title.show();
    /*QLabel title = QLabel();
    title.setPixmap(titleImage);
    title.setMask(titleImage.mask());
    title.setParent(this);
    title.show();*/

    startButton->show();
    quitButton->show();
    connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(hide()));

    connect(quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));


}

void StartMenu::startButtonClicked() {
    GameRunner gameRunner;
}

//Draws a border around the pause menu
void StartMenu::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);

    pen.setColor(Qt::darkGreen);
    painter.setPen(pen);
    painter.drawRect(0, 0, width() - 1, height() - 1);

    QPixmap titleImage = QPixmap(":/images/title2.png");
    painter.drawPixmap((width() / 2) - 373.5, 175, titleImage);

    QWidget::paintEvent(e);
}
