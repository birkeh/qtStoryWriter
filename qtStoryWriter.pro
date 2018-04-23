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
    }
}

win32-g++ {
    message("mingw")
}

unix {
    message("*nix")
}


SOURCES += \
        main.cpp \
        cmainwindow.cpp \
    ctextdocument.cpp \
    common.cpp \
    ctextedit.cpp \
    cstructurewindow.cpp \
    cwidget.cpp \
    cstorybook.cpp \
    cbook.cpp \
    cpart.cpp \
    cchapter.cpp \
    cscene.cpp \
    ccharacter.cpp \
    cpartwindow.cpp \
    cplace.cpp \
    cobject.cpp \
    crecherche.cpp \
    cimage.cpp

HEADERS += \
        cmainwindow.h \
    ctextdocument.h \
    common.h \
    ctextedit.h \
    cstructurewindow.h \
    cwidget.h \
    cstorybook.h \
    common.h \
    cbook.h \
    cpart.h \
    cchapter.h \
    cscene.h \
    ccharacter.h \
    cpartwindow.h \
    cplace.h \
    cobject.h \
    crecherche.h \
    cimage.h

FORMS += \
        cmainwindow.ui \
    cstructurewindow.ui \
    cpartwindow.ui

DISTFILES += \
    storyBook.project

RESOURCES += \
    qtstorywriter.qrc
