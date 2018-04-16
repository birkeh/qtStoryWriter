#-------------------------------------------------
#
# Project created by QtCreator 2018-03-26T11:30:37
#
#-------------------------------------------------

QT       += core gui xml sql

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

win32-msvc* {
    contains(QT_ARCH, i386) {
        message("msvc 32-bit")
    } else {
        message("msvc 64-bit")
        INCLUDEPATH += C:/dev/3rdParty/quazip/include
        DEPENDPATH += C:/dev/3rdParty/quazip/include
        LIBS += C:/dev/3rdParty/quazip/msc/lib/quazip.lib
        INCLUDEPATH += C:/dev/3rdParty/zlib/include
        DEPENDPATH += C:/dev/3rdParty/zlib/include
        LIBS += C:/dev/3rdParty/zlib/msc/lib/zlib.lib
    }
}

win32-g++ {
    message("mingw")
    INCLUDEPATH += C:/dev/3rdParty/quazip/include
    DEPENDPATH += C:/dev/3rdParty/quazip/include
    LIBS += -LC:/dev/3rdParty/quazip/gcc/lib -lquazip
    INCLUDEPATH += C:/dev/3rdParty/zlib/include
    DEPENDPATH += C:/dev/3rdParty/zlib/include
    LIBS += -LC:/dev/3rdParty/zlib/gcc/lib -lz
}

unix {
    LIBS	+= -lquazip
}


SOURCES += \
        main.cpp \
        cmainwindow.cpp \
    cdocumentreader.cpp \
    cdocumentwriter.cpp \
    ctextdocument.cpp \
    common.cpp \
    ctextedit.cpp \
    cstructurewindow.cpp \
    cwidget.cpp \
    cstorybook.cpp \
    cbook.cpp

HEADERS += \
        cmainwindow.h \
    cdocumentreader.h \
    cdocumentwriter.h \
    ctextdocument.h \
    common.h \
    ctextedit.h \
    cstructurewindow.h \
    cwidget.h \
    cstorybook.h \
    common.h \
    cbook.h

FORMS += \
        cmainwindow.ui \
    cstructurewindow.ui

DISTFILES += \
    storyBook.project

RESOURCES += \
    qtstorywriter.qrc
