#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPalette>
#include <QPaintEvent>

class GameOver: public QWidget
{
	Q_OBJECT
public:
	GameOver();
	void paintEvent(QPaintEvent* e);

private slots:
	void returnClicked();
};

