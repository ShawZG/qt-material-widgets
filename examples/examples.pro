QT += core gui widgets
TEMPLATE = app
SOURCES = mainwindow.cpp \
    main.cpp \
    avatarsettingseditor.cpp \
    badgesettingseditor.cpp \
    checkboxsettingseditor.cpp \
    fabsettingseditor.cpp \
    raisedbuttonsettingseditor.cpp \
    flatbuttonsettingseditor.cpp \
    iconbuttonsettingseditor.cpp \
    progresssettingseditor.cpp \
    circularprogresssettingseditor.cpp \
    slidersettingseditor.cpp \
    ../components/qtmaterialradiobutton.cpp \
    radiobuttonsettingseditor.cpp
HEADERS = mainwindow.h \
    avatarsettingseditor.h \
    badgesettingseditor.h \
    checkboxsettingseditor.h \
    fabsettingseditor.h \
    raisedbuttonsettingseditor.h \
    flatbuttonsettingseditor.h \
    iconbuttonsettingseditor.h \
    progresssettingseditor.h \
    circularprogresssettingseditor.h \
    slidersettingseditor.h \
    ../components/qtmaterialradiobutton_p.h \
    ../components/qtmaterialradiobutton.h \
    radiobuttonsettingseditor.h
LIBS += ../components/libcomponents.a
INCLUDEPATH += ../components/
TARGET = ../examples-exe

RESOURCES += \
    examples.qrc

FORMS += \
    avatarsettingsform.ui \
    badgesettingsform.ui \
    checkboxsettingsform.ui \
    fabsettingsform.ui \
    flatbuttonsettingsform.ui \
    iconbuttonsettingsform.ui \
    progresssettingsform.ui \
    circularprogresssettingsform.ui \
    slidersettingsform.ui \
    radiobuttonsettingsform.ui
