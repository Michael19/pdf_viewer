TEMPLATE = app

CONFIG += c++11

QT += widgets

HEADERS += mainwindow.h

SOURCES += mainwindow.cpp\
           main.cpp

RESOURCES += pdfviewer.qrc

INCLUDEPATH += ../qpdflib
INCLUDEPATH += ../stalking
INCLUDEPATH += ../mapper

CONFIG(debug, debug|release) {
    win32:LIBS += -L$$OUT_PWD/../qpdflib/debug
} else {
    win32:LIBS += -L$$OUT_PWD/../qpdflib/release
}
win32:LIBS += qpdf.lib

unix:LIBS += -L$$OUT_PWD/../qpdflib
unix:LIBS += -lqpdf

unix:LIBS += -L$$OUT_PWD/../stalking
unix:LIBS += -lstalking

unix:LIBS += -L$$OUT_PWD/../mapper
unix:LIBS += -lmapper
