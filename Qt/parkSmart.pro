QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = parkSmart

# You can make your code fail to compile if it uses deprecated APIs.  # In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ParkingStructure.cpp \
    database.cpp \
    filters.cpp \
    findpark.cpp \
    freesearch.cpp \
    main.cpp \
    osmApi.cpp \
    user.cpp \
    login.cpp


HEADERS += \
    ParkingStructure.h \
    database.h \
    filters.h \
    findpark.h \
    freesearch.h \
    osmApi.h \
    user.h \
    login.h

FORMS += \
    findpark.ui \
    freesearch.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += /opt/homebrew/Cellar/nlohmann-json/3.11.3/include
INCLUDEPATH += /opt/homebrew/opt/curl/include
LIBS += -L/opt/homebrew/opt/curl/lib -lcurl
