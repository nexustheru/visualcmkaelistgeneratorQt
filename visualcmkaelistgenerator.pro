#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T11:35:56
#
#-------------------------------------------------

QT       += core gui


INCLUDEPATH +="C:\Users\tess\Documents\Visual Studio 2013\Projects\boost_1_60_0"
LIBS +="C:\Users\tess\Documents\Visual Studio 2013\Projects\boost_1_60_0\libs\libboost_filesystem-vc120-mt-1_60.lib"
LIBS +="C:\Users\tess\Documents\Visual Studio 2013\Projects\boost_1_60_0\libs\libboost_system-vc120-mt-1_60.lib"
LIBS +="C:\Users\tess\Documents\Visual Studio 2013\Projects\boost_1_60_0\libs\libboost_program_options-vc120-mt-1_60.lib"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualcmkaelistgenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
