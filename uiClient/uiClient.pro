#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T14:36:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uiClient
TEMPLATE = app


SOURCES += main.cpp\
        uiclient.cpp

HEADERS  += uiclient.hpp

FORMS    += uiclient.ui
unix:LIBS += -lboost_system
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lchat
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lchat
else:unix: LIBS += -L$$PWD/../lib/ -lchat

INCLUDEPATH += $$PWD/../lib/includes
DEPENDPATH += $$PWD/../lib/includes

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/release/libchat.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/debug/libchat.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/release/chat.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/debug/chat.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/libchat.a
