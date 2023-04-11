QT       += core gui \
            multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += /Zc:__cplusplus

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bullet.cpp \
    Enemy.cpp \
    Explosion.cpp \
    GameRunner.cpp \
    PauseMenu.cpp \
    StartMenu.cpp \
    Tank.cpp \
    main.cpp
    Explosion.cpp
    GameRunner.cpp
    PauseMenu.cpp
    StartMenu.cpp
    Tank.cpp
    Obstacles.cpp
    

HEADERS += \
    Bullet.h \
    Enemy.h \
    Explosion.h \
    GameRunner.h \
    MainHeader.h \
    PauseMenu.h \
    StartMenu.h \
    Tank.h
    GameRunner.h
    PauseMenu.h
    StartMenu.h
    Tank.h
    Obstacles.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT_AUTO_SCREEN_SCALE_FACTOR=true
RESOURCES += \
    res.qrc
