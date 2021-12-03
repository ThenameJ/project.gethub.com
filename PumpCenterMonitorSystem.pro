#-------------------------------------------------
#
# Project created by QtCreator 2021-10-25T14:21:21
#
#-------------------------------------------------

QT       += core gui
QT       += core network
QT       += sql
QT       += multimedia
RC_ICONS = pump.ico


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

include(server/server.pri)
include(super/super.pri)
include(resource/resource.pri)
include(thirdparty/thirdparty.pri)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=

