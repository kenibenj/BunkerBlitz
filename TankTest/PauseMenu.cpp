#include "PauseMenu.h"
#include <QPushButton>
#include "GameRunner.h"
#include "MainHeader.h"

PauseMenu::PauseMenu() {
	setFixedSize(200, 300);
	setWindowTitle("Pause");
	QPushButton* resumeButton = new QPushButton("Resume", this);
	QPushButton* quitButton = new QPushButton("Quit", this);
	resumeButton->setGeometry(width() / 2 - 40, height() / 2, 80, 30);
	quitButton->setGeometry(width() / 2 - 40, (height() / 2) + 30, 80, 30);

	resumeButton->show();
	quitButton->show();
	connect(resumeButton, SIGNAL(clicked()), this, SLOT(resumeButtonClicked()));
	connect(quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
}

void PauseMenu::resumeButtonClicked() {
	GameRunner::startTimer();
	hide();

}