#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPixmap>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Explosion( QGraphicsItem* parent = nullptr);
    void removeExplosion();

private slots:
    void frame();

private:

    QMediaPlayer* explosionPlayer;

    QAudioOutput* explosionOutput;

    int counter;
    float explosionLength;
};