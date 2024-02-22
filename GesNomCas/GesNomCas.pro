QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datosempleado.cpp \
    datosempresa.cpp \
    datospersonales.cpp \
    funcaux.cpp \
    importardatos.cpp \
    importarincidencias.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    registro.cpp \
    registroretribuciones.cpp

HEADERS += \
    datosempleado.h \
    datosempresa.h \
    datospersonales.h \
    funcaux.h \
    importardatos.h \
    importarincidencias.h \
    login.h \
    mainwindow.h \
    registro.h \
    registroretribuciones.h

FORMS += \
    datosempleado.ui \
    datosempresa.ui \
    datospersonales.ui \
    importardatos.ui \
    importarincidencias.ui \
    login.ui \
    mainwindow.ui \
    registro.ui \
    registroretribuciones.ui

#
# Añadido por mi para usar sqlite3
#
QT += sql

#
# Añadido por mi para usar Cryptopp
#
LIBS += -lcryptopp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes/imagenes.qrc

DISTFILES +=
