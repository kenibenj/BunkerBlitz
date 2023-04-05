#include "Spawner.h"

Spawner::Spawner(QGraphicsScene* scene, QObject* parent)
    : QObject(parent),
      m_scene(scene)
{
    // Load images
    m_images.append(QPixmap(":/images/Ammobox.png"));
    m_images.append(QPixmap(":/images/GEARZ1.png"));
    m_images.append(QPixmap(":/images/Shield.png"));

    // Spawn the images
    for (int i = 0; i < m_numImages; i++)
    {
        spawnImage();
    }
}

void Spawner::spawnImage()
{
    // Choose a random image from the vector
    QPixmap image = m_images[QRandomGenerator::global()->bounded(m_images.size())];

    // Create and add image to scene
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(image);
    item->setPos(QRandomGenerator::global()->bounded(2400 - m_imageWidth),
        QRandomGenerator::global()->bounded(1800 - m_imageHeight));
    item->setData(Qt::UserRole, "obstacle"); // set data to identify the item as an obstacle
    item->setZValue(-6);
    m_scene->addItem(item);
}