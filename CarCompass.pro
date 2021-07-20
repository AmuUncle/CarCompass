#-------------------------------------------------
#
# Project created by QtCreator 2021-07-19T16:26:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarCompass
TEMPLATE = app
DESTDIR = bin

include ($$PWD/public/public.pri)
INCLUDEPATH += $$PWD/include

SOURCES += source/main.cpp\
        source/carcompass.cpp \
    source/basebutton.cpp \
    source/voicecontrolpane.cpp \
    source/dropdownbox.cpp \
    source/basewidget.cpp

HEADERS  += include/carcompass.h \
    include/basebutton.h \
    include/global.h \
    include/voicecontrolpane.h \
    include/dropdownbox.h \
    include/basewidget.h

RESOURCES += \
    res/res.qrc

RC_FILE +=  \
    res/res.rc

FORMS += \
    ui/dropdownbox.ui
