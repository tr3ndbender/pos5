QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../TinyXML2_Static/build/Qt_6_11_2_for_macOS_Debug/release/ -lTinyXML2_Static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../TinyXML2_Static/build/Qt_6_11_2_for_macOS_Debug/debug/ -lTinyXML2_Static
else:unix: LIBS += -L$$PWD/../TinyXML2_Static/build/Qt_6_11_2_for_macOS_Debug/ -lTinyXML2_Static

INCLUDEPATH += $$PWD/../TinyXML2_Static
DEPENDPATH += $$PWD/../TinyXML2_Static
