#pragma once
#include <QWidget>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QScreen>
#include <QPaintEvent>
#include <QPixmap>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
class StartMenu : public QWidget
{
	Q_OBJECT
public:
	explicit StartMenu(QWidget* parent = nullptr);

	void paintEvent(QPaintEvent* e);

public slots:
	void startButtonClicked();
    void instructionButtonClicked();
private:
	QAudioOutput* backgroundAudioOutput;
	QMediaPlayer* backgroundMediaPlayer;
};
