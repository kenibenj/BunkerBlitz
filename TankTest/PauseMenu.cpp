#include "PauseMenu.h"
#include <QPushButton>
#include "GameRunner.h"
#include "MainHeader.h"
#include <QProcess>
#include <QDebug>
#include <QApplication>
#include <QFont>
PauseMenu::PauseMenu() {
    setFixedSize(250, 300);
	setWindowTitle("Pause");
	setWindowFlags(Qt::FramelessWindowHint);
    move((1920 / 2) - 125, (1080 / 2) -150);
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
    resumeButton->setGeometry(width() / 2 - 70, 75, 140, 60);
    quitButton->setGeometry(width() / 2 - 70, 205, 140, 60);
    returnButton->setGeometry(width() / 2 - 70, 140, 140, 60);
	//Adjusting style for the buttons
    resumeButton->setStyleSheet("QPushButton {color: blqack; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen;} } QPushButton:pressed { background-color: darkGreen;}");
    quitButton->setStyleSheet("QPushButton {color: blqack; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen;} } QPushButton:pressed { background-color: darkGreen;}");
    returnButton->setStyleSheet("QPushButton {color: blqack; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen;} } QPushButton:pressed { background-color: darkGreen;}");
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
	QBrush brush;
	brush.setColor(QColor(144, 238, 144));
	brush.setStyle(Qt::SolidPattern);
	painter.fillRect(0, 0, 250, 50, brush);
	pen.setColor(Qt::darkGreen);
	painter.setPen(pen);
	painter.drawRect(0, 0, width()-1, height()-1);
    painter.drawLine(0,50,250, 50);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setFont(QFont("Times", 30));
    painter.drawText(75, 40, "Pause");
	
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
