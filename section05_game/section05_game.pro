#-------------------------------------------------
#
# Project created by QtCreator 2023-10-29T22:41:02
#
#-------------------------------------------------

QT       += core gui network
QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = section05_game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        gameover.cpp \
        gamestate.cpp \
        ghostplayer.cpp \
        main.cpp \
        maze.cpp \
        network.cpp \
        player.cpp \
        score.cpp \
        puck.cpp \
        obstacle.cpp \
        speedpowerup.cpp \
        victorypickup.cpp

HEADERS += \
        gameover.h \
        gamestate.h \
        ghostplayer.h \
        maze.h \
        network.h \
        player.h \
        score.h \
        puck.h \
        obstacle.h \
        speedpowerup.h \
        victorypickup.h

FORMS += \
        gameover.ui \
        maze.ui \
        network.ui \
        score.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
