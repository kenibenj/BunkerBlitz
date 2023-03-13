#pragma once
#ifndef MYTEST_H
#define MYTEST_H

#include <QtTest/QtTest>
#include <QObject>

class MyTest : public QObject
{
    Q_OBJECT

private slots:
    void testFoo()
    {
        QCOMPARE(1 + 1, 2);
    }
};

#endif // MYTEST_H
