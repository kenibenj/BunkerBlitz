#include "StartMenu.h"
#include "MainHeader.h"
#include "Tank.h"
#include "GameRunner.h"
#include <QWindow>

StartMenu::StartMenu(QWidget* parent) : QWidget{parent}
{
    setFixedSize(1200, 900);

    //Title for the window
    setWindowTitle("Bunker Blitz");

    //Set the icon to the window
    setWindowIcon(QIcon::fromTheme("myicon", QIcon("myicon.png")));

    QPushButton* startButton = new QPushButton("Start", this);
    QPushButton* quitButton = new QPushButton("Quit", this);
    startButton->setGeometry(width() / 2 - 50, height() / 2 - 30, 100, 60);
    quitButton->setGeometry(width() / 2 - 50, (height() / 2) + 30, 100, 60);

    startButton->show();
    quitButton->show();
    connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));


}

void StartMenu::startButtonClicked() {
    GameRunner gameRunner;
}