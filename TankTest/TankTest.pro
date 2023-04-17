QT       += core gui \
            multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += /Zc:__cplusplus

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ammo.cpp \
    Boss.cpp \
    Bullet.cpp \
    Enemy.cpp \
    Explosion.cpp \
    GameOver.cpp \
    GameRunner.cpp \
    Obstacles.cpp \
    PauseMenu.cpp \
    Repair.cpp \
    Shield.cpp \
    Spawner.cpp \
    StartMenu.cpp \
    Tank.cpp \
    instructions.cpp \
    main.cpp
    Explosion.cpp
    GameRunner.cpp
    PauseMenu.cpp
    StartMenu.cpp
    Tank.cpp
    

HEADERS += \
    Ammo.h \
    Boss.h \
    Bullet.h \
    Enemy.h \
    Explosion.h \
    GameOver.h \
    GameRunner.h \
    MainHeader.h \
    Obstacles.h \
    PauseMenu.h \
    Repair.h \
    Shield.h \
    Spawner.h \
    StartMenu.h \
    Tank.h \
    instructions.h
    GameRunner.h
    PauseMenu.h
    StartMenu.h
    Tank.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT_AUTO_SCREEN_SCALE_FACTOR=true
RESOURCES += \
    res.qrc
