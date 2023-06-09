QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BJ_game.cpp \
    gamebar.cpp \
    main.cpp \
    BJ_window.cpp \
    menu.cpp \
    skin_menu.cpp

HEADERS += \
    BJ_game.h \
    BJ_window.h \
    gamebar.h \
    menu.h \
    skin_menu.h

FORMS += \
    BJwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
