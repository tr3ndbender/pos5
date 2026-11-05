QT += core gui

TEMPLATE = lib
DEFINES += PLUGIN_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEPENDPATH += sdk
INCLUDEPATH += $$PWD/sdk/include/
LIBS += -L$$PWD/../lib -lFormen_Factory
DESTDIR = $$PWD/../lib

SOURCES += \
    unregelmaessigesdreieck.cpp \
    rechtwinkligesdreieck.cpp \
    stern.cpp \
    sechseck.cpp \
    regelmaessigespolygon.cpp \
    raute.cpp \
    ellipse.cpp \
    circle.cpp \
    dreieck.cpp \
    paralellogramm.cpp \
    rectangle.cpp \
    register.cpp \
    square.cpp \
    trapez.cpp

HEADERS += \
    unregelmaessigesdreieck.h \
    rechtwinkligesdreieck.h \
    stern.h \
    sechseck.h \
    regelmaessigespolygon.h \
    raute.h \
    ellipse.h \
    circle.h \
    dreieck.h \
    paralellogramm.h \
    rectangle.h \
    register.h \
    square.h \
    trapez.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

QMAKE_RPATHDIR += $$PWD/../lib
