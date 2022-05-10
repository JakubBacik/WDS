QT       += core gui
QT       += serialport
QT       += core gui charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/CircleAnimation.cpp \
    src/CommunicationAndMyQThread.cpp \
    src/ConnectionDialog.cpp \
    src/DataBuffer.cpp \
    src/Mainwindow.cpp \
    src/MyQChart.cpp \
    src/RecievedData.cpp \
    src/main.cpp

HEADERS += \
    inc/CircleAnimation.hh \
    inc/CommunicationAndMyQThread.hh \
    inc/ConnectionDialog.hh \
    inc/DataBuffer.hh \
    inc/Mainwindow.hh \
    inc/MyQChart.hh \
    inc/ui_connectionwitharduino.hh

FORMS += \
    ui/connectionwitharduino.ui \
    ui/mainwindow.ui

TRANSLATIONS += \
    lang/ParkingSensor_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
