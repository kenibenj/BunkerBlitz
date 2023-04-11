#include "GameOver.h"
#include "MainHeader.h"
#include <QProcess>
#include <QDebug>
#include <QPalette>
#include "GameRunner.h"
#include <QFont>

GameOver::GameOver()
{
	GameRunner::gameOverTimers();
    setFixedSize(320, 225);
	setWindowFlag(Qt::FramelessWindowHint);
	setWindowFlag(Qt::WindowStaysOnTopHint);
    move((1920 / 2) - 160, (1080 / 2) -112.5);
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
    quitButton->setGeometry(width() / 2 - 70, height() - 80, 140, 60);
    returnButton->setGeometry(width() / 2 - 70, height() -150, 140, 60);
	//Adjusting style for the buttons
    quitButton->setStyleSheet("QPushButton {color: blqack; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen;} } QPushButton:pressed { background-color: darkGreen;}");
    returnButton->setStyleSheet("QPushButton {color: blqack; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen;} } QPushButton:pressed { background-color: darkGreen;}");
	returnButton->show();
	quitButton->show();
	connect(quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
	connect(returnButton, SIGNAL(clicked()), this, SLOT(returnClicked()));

}


void GameOver::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	QPen pen;
	QBrush brush;
	brush.setColor(QColor(144, 238, 144));
	brush.setStyle(Qt::SolidPattern);
	painter.fillRect(0, 0, 320, 50, brush);
	pen.setColor(Qt::darkGreen);
	painter.setPen(pen);
	painter.drawRect(0, 0, width() - 1, height() - 1);
    painter.drawLine(0, 50, 320, 50);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setFont(QFont("Times", 30));
    painter.drawText(60, 40, "Game Over");

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
