QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core network
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authserver.cpp \
    card.cpp \
    databasemanage.cpp \
    detectwinner.cpp \
    exceptions.cpp \
    main.cpp \
    mainwindow.cpp \
    user.cpp

HEADERS += \
    authserver.h \
    card.h \
    databasemanage.h \
    detectwinner.h \
    exceptions.h \
    mainwindow.h \
    user.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
