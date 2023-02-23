#pragma once
#include <QTimer>


class GameRunner : public QObject
{
	Q_OBJECT
public:
	GameRunner();
	static void pauseTimer();
	static void startTimer();

};
