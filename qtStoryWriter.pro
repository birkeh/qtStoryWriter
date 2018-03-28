#-------------------------------------------------
#
# Project created by QtCreator 2018-03-26T11:30:37
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtStoryWriter
TEMPLATE = app
qtHaveModule(printsupport): QT += printsupport

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        cmainwindow.cpp \
    cdocumentreader.cpp \
    cdocumentwriter.cpp \
    ctextdocument.cpp \
    common.cpp

HEADERS += \
        cmainwindow.h \
    cdocumentreader.h \
    cdocumentwriter.h \
    ctextdocument.h \
    common.h

FORMS += \
        cmainwindow.ui

DISTFILES += \
    example.html

RESOURCES += \
    qtstorywriter.qrc

INCLUDEPATH += C:/dev/3rdParty/zlib
LIBS += -LC:/dev/3rdParty/zlib -lz
INCLUDEPATH += C:/dev/3rdParty/quazip
LIBS += -LC:/dev/3rdParty/quazip/release -lquazip
