QT       += core gui
QT +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += link_pkgconfig
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    beginwindow.cpp \
    editwindow.cpp \
    exceptions.cpp \
    forgotpswwindow.cpp \
    main.cpp \
    client.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    signinwindow.cpp \
    signupwindow.cpp

HEADERS += \
    beginwindow.h \
    client.h \
    editwindow.h \
    exceptions.h \
    forgotpswwindow.h \
    mainwindow.h \
    menuwindow.h \
    signinwindow.h \
    signupwindow.h

FORMS += \
    client.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
MOC_DIR = .moc
OBJECTS_DIR = .obj

RESOURCES += \
    images.qrc

 QT += widgets
