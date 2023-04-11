#pragma once
#ifndef MYTEST_H
#define MYTEST_H



#include <QtTest/QtTest>
#include <QObject>
#include "../TankTest/Tank.h"
#include "../TankTest/Tank.cpp"
#include "../TankTest/Obstacles.h"
#include "../TankTest/Obstacles.cpp"
#include "../TankTest/PauseMenu.cpp"
#include "../TankTest/PauseMenu.h"
#include "../TankTest/Enemy.h"
#include "../TankTest/Enemy.cpp"
#include "../TankTest/Bullet.h"
#include <QTimer>
#include "../TankTest/Bullet.cpp"
#include "../TankTest/Explosion.h"
#include "../TankTest/Explosion.cpp"
#include "../TankTest/GameRunner.h"
#include "../TankTest/GameRunner.cpp"


class MyGraphicsItem : public QGraphicsItem
{
public:
    QRectF boundingRect() const override {
        // Implement boundingRect() function for test purpose
        return QRectF(-10, -10, 20, 20);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override {
        // Implement paint() function if neeed for testing
    }
};

class MyTest : public QObject
{
    
private:
    Tank* tank;
    
private slots:
    void testFoo()
    {
        QCOMPARE(1 + 1, 2);
    }

    void initTestCase()
    {
        // Create a QGraphicsView object
        QGraphicsView* view = new QGraphicsView();

        // Create a parent QGraphicsItem object
        MyGraphicsItem* parent = new MyGraphicsItem();

        // Create a Tank object
        tank = new Tank(view, parent);

        //create a sceneand add tank to it
        QGraphicsScene scene;
        view->setScene(&scene);
        scene.addItem(tank);


    }

  
    void testMove()
    {
        QGraphicsView view;
        Tank tank(&view);
       

        // A QSignalSpy is a Qt class that can be used to monitor signals emitted by an object
        QSignalSpy spy(&tank, &Tank::positionChanged);

        // Test when no keys are pressed
        QVERIFY(!spy.count());

        // Test when the up key is pressed
        tank.keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_W, Qt::NoModifier));
        QVERIFY(spy.count() == 1);

        // Test when the down key is pressed
        tank.keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_S, Qt::NoModifier));
        QVERIFY(spy.count() == 2);

        // Test when the left key is pressed
        tank.keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_A, Qt::NoModifier));
        QVERIFY(spy.count() == 3);

        // Test when the right key is pressed
        tank.keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_D, Qt::NoModifier));
        QVERIFY(spy.count() == 4);

        // Test when all keys are released
        tank.keyReleaseEvent(new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_W, Qt::NoModifier));
        tank.keyReleaseEvent(new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_S, Qt::NoModifier));
        tank.keyReleaseEvent(new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_A, Qt::NoModifier));
        tank.keyReleaseEvent(new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_D, Qt::NoModifier));
        QVERIFY(spy.count() == 0);
    }

    void testCreateTurret() {
        QGraphicsView view;
        Tank tank(&view);

        // Test that the turret is created
        QVERIFY(tank.getTurret() != nullptr);

        // Test that the turret is positioned correctly
        QCOMPARE(tank.getTurret()->x(), tank.x() + tank.boundingRect().width() / 2 - tank.getTurret()->boundingRect().width() / 2);
        QCOMPARE(tank.getTurret()->y(), tank.y() + tank.boundingRect().height() / 2 - tank.getTurret()->boundingRect().height() / 2 - 10);

        // Test that the turret has the correct pixmap
        QCOMPARE(tank.getTurret()->pixmap(), QPixmap(":/images/greenTurret.png"));

      

        // Test that the turret is added to the scene
        //QVERIFY(tank.scene()->contains(tank.getTurret()));
    }

    void cleanupTestCase()
    {
        delete tank;
    }
};


#endif // MYTEST_H
