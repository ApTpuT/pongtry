#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T12:55:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pongtry

TEMPLATE = app


SOURCES += main.cpp \
    bitmap.cpp  \
    fixedfann.c \
    fann_train_data.c \
    fann_train.c \
    fann_io.c \
    fann_error.c \
    fann_cascade.c \
    fann.c \
    learningprocess.cpp \
    mainwindow.cpp


HEADERS += \
    bitmap.h    \
    fixedfann.h \
    fann_train.h \
    fann_io.h \
    fann_internal.h \
    fann_error.h \
    fann_data.h \
    fann_cpp.h \
    fann_cascade.h \
    fann_activation.h \
    fann.h \
    config.h \
    compat_time.h \
    learningprocess.h \
    mainwindow.h

FORMS    += mainwindow.ui

win32:LIBS += E:\Work\OCR-master\FANN-2.2.0-Source\bin\fannfixed.dll
