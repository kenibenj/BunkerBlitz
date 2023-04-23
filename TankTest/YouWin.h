#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPalette>
#include <QPaintEvent>

class YouWin : public QWidget
{
	Q_OBJECT
public:
	YouWin();
	void paintEvent(QPaintEvent* e);

private slots:
	void returnClicked();
};

