QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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

!contains(QMAKE_HOST.arch, x86_64) {
    TARGET = DIYSystemMemoryDump32
} else {
    TARGET = DIYSystemMemoryDump64
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



# ICO
RC_ICONS = NewWorld.ico

# RESOURCES
RESOURCES += QDarkStyleSheet/qdarkstyle/dark/style.qrc
RESOURCES += QDarkStyleSheet/qdarkstyle/light/style.qrc
RESOURCES += QDarkStyleSheet/qdarkstyle/X64DBGDark/style.qrc

#UAC
QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:"level='requireAdministrator'"
