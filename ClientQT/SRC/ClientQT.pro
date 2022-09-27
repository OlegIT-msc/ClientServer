QT       += core gui network qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG(debug, debug|release) {
 TARGET = ../../bin/ClientQTD
 DESTDIR = $$PWD/bin
} else {
 TARGET = ../../bin/ClientQT
 DESTDIR = $$PWD/bin
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../CommonClient/clienttcp.cpp \
    ../../CommonClient/service.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../Common/Common.h \
    ../../CommonClient/clienttcp.h \
    ../../CommonClient/service.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
