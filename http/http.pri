QT += network
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include(../tcp/tcp.pri)

HEADERS += \
    $$PWD/httpconnection.h \
    $$PWD/httpserver.h

SOURCES += \
    $$PWD/httpconnection.cpp \
    $$PWD/httpserver.cpp
