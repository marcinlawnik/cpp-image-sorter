#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T11:49:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = v3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    helpdialog.cpp \
    imagecontroller.cpp \
    imagelistdialog.cpp \
    goodimagelistdialog.cpp \
    imagecopier.cpp \
    reportdialog.cpp \
    settingsdialog.cpp \
    thumbsprogressdialog.cpp

HEADERS  += mainwindow.h \
    helpdialog.h \
    imagecontroller.h \
    imagelistdialog.h \
    goodimagelistdialog.h \
    imagecopier.h \
    reportdialog.h \
    settingsdialog.h \
    thumbsprogressdialog.h

FORMS    += mainwindow.ui \
    helpdialog.ui \
    imagelistdialog.ui \
    goodimagelistdialog.ui \
    reportdialog.ui \
    settingsdialog.ui \
    thumbsprogressdialog.ui

CONFIG   += static

DISTFILES += \
    .gitignore \
    design.md \
    license.md \
    watermark.jpg \
    watermark.png

#graphicsmagick config

INCLUDEPATH += "C:\MinGW\msys\1.0\local\include\GraphicsMagick"
INCLUDEPATH += "C:\MinGW\msys\1.0\local\lib"

QMAKE_CXXFLAGS += -I"C:\MinGW\msys\1.0\local\include\GraphicsMagick" -D_LIB -D_MT

LIBS += -L"C:\MinGW\msys\1.0\local\lib"
LIBS += -lGraphicsMagick++ -lGraphicsMagick -ljpeg -lpng15 -lz -lgdi32 -lm -lgomp -lpthread

RESOURCES += \
    cpp-image-sorter.qrc
