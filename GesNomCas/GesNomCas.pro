QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calendario.cpp \
    calendariolaboral.cpp \
    cargarnomina.cpp \
    crearnomina.cpp \
    datosempleado.cpp \
    datosempresa.cpp \
    datospersonales.cpp \
    funcaux.cpp \
    importardatos.cpp \
    importarincidencias.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    modoficarincidencias.cpp \
    precargarnomina.cpp \
    precrearnomina.cpp \
    registro.cpp \
    registrodiasfestivos.cpp \
    registroretribuciones.cpp \
    registrovacaciones.cpp

HEADERS += \
    calendario.h \
    calendariolaboral.h \
    cargarnomina.h \
    crearnomina.h \
    datosempleado.h \
    datosempresa.h \
    datospersonales.h \
    funcaux.h \
    importardatos.h \
    importarincidencias.h \
    login.h \
    mainwindow.h \
    modoficarincidencias.h \
    precargarnomina.h \
    precrearnomina.h \
    registro.h \
    registrodiasfestivos.h \
    registroretribuciones.h \
    registrovacaciones.h

FORMS += \
    calendario.ui \
    calendariolaboral.ui \
    cargarnomina.ui \
    crearnomina.ui \
    datosempleado.ui \
    datosempresa.ui \
    datospersonales.ui \
    importardatos.ui \
    importarincidencias.ui \
    login.ui \
    mainwindow.ui \
    modoficarincidencias.ui \
    precargarnomina.ui \
    precrearnomina.ui \
    registro.ui \
    registrodiasfestivos.ui \
    registroretribuciones.ui \
    registrovacaciones.ui

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
