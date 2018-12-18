#-------------------------------------------------
#
# Project created by QtCreator 2017-01-16T14:46:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    prompt_dialog.cpp

HEADERS  += dialog.h \
    prompt_dialog.h

FORMS    += dialog.ui \
    prompt_dialog.ui

RC_FILE = icon.rc
