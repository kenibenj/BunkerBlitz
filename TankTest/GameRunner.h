#pragma once
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>


class GameRunner : public QObject
{
	Q_OBJECT
public:
	GameRunner();
	static void pauseTimer();
	static void startTimer();
public slots:
    void rePositionHUD();
    void onTankPositionChange();
private:
	QGraphicsScene* scene;
	QGraphicsView* view;
	QGraphicsPixmapItem* health1;
	QGraphicsPixmapItem* health2;
	QGraphicsPixmapItem* health3;

};
