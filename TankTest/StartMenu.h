#pragma once
#include <QWidget>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QScreen>

class StartMenu : public QWidget
{
	Q_OBJECT
public:
	explicit StartMenu(QWidget* parent = nullptr);
public slots:
	void gameRunner();

private:
	
};

