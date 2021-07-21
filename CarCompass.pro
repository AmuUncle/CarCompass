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
    source/basewidget.cpp \
    source/mainwnd.cpp \
    source/incomingcall.cpp \
    source/musicpane.cpp \
    source/compasspane.cpp

HEADERS  += include/carcompass.h \
    include/basebutton.h \
    include/global.h \
    include/voicecontrolpane.h \
    include/dropdownbox.h \
    include/basewidget.h \
    include/mainwnd.h \
    include/incomingcall.h \
    include/musicpane.h \
    include/compasspane.h

FORMS += \
    ui/dropdownbox.ui \
    ui/incomingcall.ui \
    ui/musicpane.ui \
    ui/compasspane.ui

RESOURCES += \
    res/res.qrc

RC_FILE +=  \
    res/res.rc


