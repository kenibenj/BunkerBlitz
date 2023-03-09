#pragma once
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QWidget>

class GameRunner : public QObject
{
	Q_OBJECT
public:
	GameRunner();
	static void pauseTimer();
	static void startTimer();

private:
	QGraphicsScene* scene;
	QGraphicsView* view;
	QGraphicsPixmapItem* health1;
	QGraphicsPixmapItem* health2;
	QGraphicsPixmapItem* health3;

};
