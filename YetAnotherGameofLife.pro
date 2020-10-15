
VERSION = 1.0

QT += widgets testlib
SOURCES += \
    main.cpp \
    cell.cpp \
    mainwindow.cpp \
    gameview.cpp

HEADERS += \
    cell.h \
    mainwindow.h \
    gameview.h

DISTFILES += \
    README.md

QMAKE_CXXFLAGS_RELEASE += -O3

CONFIG += debug_and_release
CONFIG += build_all

CONFIG(debug, debug|release) {
    TARGET = debug_yagol
} else {
    TARGET = yetanothergameoflife
}
