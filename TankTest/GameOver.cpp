#include "GameOver.h"
#include "MainHeader.h"
#include <QProcess>
#include <QDebug>
#include <QPalette>
GameOver::GameOver()
{
	setFixedSize(320, 420);
	setWindowFlag(Qt::FramelessWindowHint);
	setWindowFlag(Qt::WindowStaysOnTopHint);
	QPalette pal = QPalette();
	//sets the palette color to black
	pal.setColor(QPalette::Window, Qt::black);
	//Allows window to be set to a color
	setAutoFillBackground(true);
	//sets the color of the window
	setPalette(pal);

	//Creating the buttons
	QPushButton* quitButton = new QPushButton("Quit", this);
	QPushButton* returnButton = new QPushButton("Return to Main Menu", this);
	quitButton->setGeometry(width() / 2 - 70, 350, 140, 60);
	returnButton->setGeometry(width() / 2 - 70, 280, 140, 60);
	//Adjusting style for the buttons
	quitButton->setStyleSheet("color: black; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen; ");
	returnButton->setStyleSheet("color: black; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen; ");
	returnButton->show();
	quitButton->show();
	connect(quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
	connect(returnButton, SIGNAL(clicked()), this, SLOT(returnClicked()));

}


void GameOver::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	QPen pen;
	pen.setColor(Qt::green);
	painter.setPen(pen);
	painter.drawRect(0, 0, width() - 1, height() - 1);

	QWidget::paintEvent(e);
}
void GameOver::returnClicked() {
	//Closes the current running process
	qApp->quit();
	//Restarts the main function
	QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
	//Deletes the gameover screen
	delete this;
}