#include "PauseMenu.h"
#include <QPushButton>
#include "GameRunner.h"
#include "MainHeader.h"

PauseMenu::PauseMenu() {
	setFixedSize(100, 80);
	setWindowTitle("Pause");
	setWindowFlags(Qt::FramelessWindowHint);
	QPalette pal = QPalette();
	//Sets the palette color to black
	pal.setColor(QPalette::Window, Qt::black);

	//Allows window to be set to a color
	setAutoFillBackground(true);
	//Sets the color of the window
	setPalette(pal);

	//setStyleSheet("border: 1px solid green");


	QPushButton* resumeButton = new QPushButton("Resume", this);
	QPushButton* quitButton = new QPushButton("Quit", this);
	resumeButton->setGeometry(width() / 2 - 40, 10, 80, 30);
	quitButton->setGeometry(width() / 2 - 40, 40, 80, 30);

	resumeButton->show();
	quitButton->show();
	connect(resumeButton, SIGNAL(clicked()), this, SLOT(resumeButtonClicked()));
	connect(quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
}

void PauseMenu::resumeButtonClicked() {
	GameRunner::startTimer();
	hide();

}

void PauseMenu::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Escape) {
		GameRunner::startTimer();
		hide();
	}
}
//Draws a border around the pause menu
void PauseMenu::paintEvent(QPaintEvent* e) {
	QPainter painter(this);
	QPen pen;
	pen.setColor(Qt::green);
	painter.setPen(pen);
	painter.drawRect(0, 0, width(), height());
	
	QWidget::paintEvent(e);
}