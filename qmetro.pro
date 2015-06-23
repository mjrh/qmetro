#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T18:53:15
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qmetro
TEMPLATE = app

MAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread

CONFIG += c++11

SOURCES += main.cpp\
        qmetro.cpp \
    metronompuls.cpp

HEADERS  += qmetro.h \
    metronompuls.h

FORMS    += qmetro.ui
