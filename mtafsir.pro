#-------------------------------------------------
#
# Project created by QtCreator 2013-09-03T10:48:54
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mtafsir
TEMPLATE = app
DESTDIR = usr/bin

SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    dialogoptions.cpp \
    buttoncolor.cpp

HEADERS  += mainwindow.h \
    database.h \
    dialogoptions.h \
    buttoncolor.h

FORMS    += mainwindow.ui \
    dialogoptions.ui \
    dialogAbout.ui

RESOURCES += \
    images.qrc
# install

MKDIR = mkdir -p /usr/share/mtafsir

 data.files =usr/share/mtafsir*
 data.path=/usr/share/

 desktopfile.files = mtafsir.desktop
 desktopfile.path = /usr/share/applications

 icon.files = usr/share/icons/hicolor/22x22/apps/mtafsir.png
 icon.path = /usr/share/icons/hicolor/22x22/apps
 icon1.files = usr/share/icons/hicolor/24x24/apps/mtafsir.png
 icon1.path = /usr/share/icons/hicolor/24x24/apps
 icon2.files = usr/share/icons/hicolor/32x32/apps/mtafsir.png
 icon2.path = /usr/share/icons/hicolor/32x32/apps
 icon3.files = usr/share/icons/hicolor/48x48/apps/mtafsir.png
 icon3.path = /usr/share/icons/hicolor/48x48/apps
 icon4.files = usr/share/icons/hicolor/64x64/apps/mtafsir.png
 icon4.path = /usr/share/icons/hicolor/64x64/apps
 icon5.files = usr/share/icons/hicolor/96x96/apps/mtafsir.png
 icon5.path = /usr/share/icons/hicolor/96x96/apps

 icon6.files = usr/share/icons/hicolor/128x128/apps/mtafsir.png
 icon6.path = /usr/share/icons/hicolor/128x128/apps

 icon7.files = usr/share/icons/hicolor/scalable/apps/mtafsir.svg
 icon7.path = /usr/share/icons/hicolor/scalable/apps

 target.path = /usr/bin

 INSTALLS +=    data \
                target \
                desktopfile\
                icon\
                icon1\
                icon2\
                icon3\
                icon4\
                icon5\
                icon6\
                icon7\
