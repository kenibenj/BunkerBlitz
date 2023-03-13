#include <QtTest/QtTest>
#include "mytest.h"


int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    MyTest test;
    QTest::qExec(&test);

    return app.exec();
}
