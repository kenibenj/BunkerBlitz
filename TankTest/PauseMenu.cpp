#include "PauseMenu.h"
#include <QPushButton>
#include "GameRunner.h"
#include "MainHeader.h"
#include <QProcess>
#include <QDebug>
PauseMenu::PauseMenu() {
	setFixedSize(160, 210);
	setWindowTitle("Pause");
	setWindowFlags(Qt::FramelessWindowHint);
	QPalette pal = QPalette();
	//Sets the palette color to black
	pal.setColor(QPalette::Window, Qt::black);

	//Allows window to be set to a color
	setAutoFillBackground(true);
	//Sets the color of the window
	setPalette(pal);



	QPushButton* resumeButton = new QPushButton("Resume", this);
	QPushButton* quitButton = new QPushButton("Quit", this);
	QPushButton* returnButton = new QPushButton("Return to Main Menu", this);
	resumeButton->setGeometry(width() / 2 - 70, 10, 140, 60);
	quitButton->setGeometry(width() / 2 - 70, 140, 140, 60);
	returnButton->setGeometry(width() / 2 - 70, 75, 140, 60);
	//Adjusting style for the buttons
	resumeButton->setStyleSheet("color: black; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen;");
	quitButton->setStyleSheet("color: black; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen; ");
	returnButton->setStyleSheet("color: black; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen; ");
	resumeButton->show();
	quitButton->show();
	connect(resumeButton, SIGNAL(clicked()), this, SLOT(resumeButtonClicked()));
	connect(quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    connect(returnButton, SIGNAL(clicked()), this, SLOT(returnButtonClicked()));
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
	painter.drawRect(0, 0, width()-1, height()-1);
	
	QWidget::paintEvent(e);
}void PauseMenu::returnButtonClicked() {
    qDebug() << "Return button clicked";
    //Closes the current running processes
    qApp->quit();
    //Restarts the main function
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    //Deletes the pausemenu
    delete this;

}
