QT += network

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/tcpserver.h \
    $$PWD/tcpconnection.h \
    $$PWD/tcpconnections.h

SOURCES += \
    $$PWD/tcpserver.cpp \
    $$PWD/tcpconnection.cpp \
    $$PWD/tcpconnections.cpp
