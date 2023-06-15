QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game.cpp \
    game_structs.cpp \
    gamebar_logic.cpp \
    gamebar_rendering.cpp \
    main.cpp \
    main_menu.cpp \
    skin_menu.cpp \
    window_logic.cpp \
    window_slots.cpp

HEADERS += \
    game.h \
    game_structs.h \
    gamebar.h \
    main_menu.h \
    skin_menu.h \
    window.h

FORMS += \
    BJwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
