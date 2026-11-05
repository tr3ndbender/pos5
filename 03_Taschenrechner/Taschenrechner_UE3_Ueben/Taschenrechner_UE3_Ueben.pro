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

# Statische Library calcLib: -L = Ordner, -l = Name ohne "lib" und ohne Endung.
# Nach Aenderung an der .pro: Build -> qmake ausfuehren. calcLib muss vorher gebaut sein.
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../calcLib/build/Qt_6_11_2_for_macOS_Debug/release/ -lcalcLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../calcLib/build/Qt_6_11_2_for_macOS_Debug/debug/ -lcalcLib
else:unix: LIBS += -L$$PWD/../calcLib/build/Qt_6_11_2_for_macOS_Debug/ -lcalcLib

INCLUDEPATH += $$PWD/../calcLib
DEPENDPATH += $$PWD/../calcLib
