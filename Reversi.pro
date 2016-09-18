#-------------------------------------------------
#
# Project created by QtCreator 2016-09-17T20:20:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reversi
TEMPLATE = app


SOURCES += main.cpp \
    cell.cpp \
    chessboard.cpp \
    guibase.cpp \
    boarddata.cpp \
    game.cpp \
    gochoice.cpp \
    idcell.cpp \
    playerid.cpp \
    players.cpp

HEADERS  += \
    cell.h \
    chessboard.h \
    guibase.h \
    boarddata.h \
    err.h \
    game.h \
    gochoice.h \
    idcell.h \
    playerid.h \
    players.h

FORMS
