#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>


#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QVector>

class Spawner : public QObject
{
    Q_OBJECT
public:
    explicit Spawner(QGraphicsScene* scene, QObject* parent = nullptr);

private:
    QGraphicsScene* m_scene;

    const int m_numImages = 10;
    const int m_imageWidth = 100;
    const int m_imageHeight = 100;

    QVector<QPixmap> m_images;

    void spawnImage();
};