QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_MACOSX_DEPLOYMENT_TARGET=14.0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graph.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    graph.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES     = application.qrc

ICON = icons/brick_game_icon.png

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/../../build/ -lsnake

INCLUDEPATH += $$PWD/../../build/
DEPENDPATH += $$PWD/../../build/

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../build/snake.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../build/libsnake.a

unix|win32: LIBS += -L$$PWD/../../build/ -ltetris

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../build/tetris.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../build/libtetris.a
