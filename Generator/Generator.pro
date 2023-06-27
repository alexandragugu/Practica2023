QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dhcp.cpp \
    dhcprequest.cpp \
    dns.cpp \
    dnsoptiuni.cpp \
    dnsquery.cpp \
    dnsupdate.cpp \
    dnswindow.cpp \
    ftp.cpp \
    http.cpp \
    httpget.cpp \
    httppost.cpp \
    icmp.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    dhcp.h \
    dhcprequest.h \
    dns.h \
    dnsoptiuni.h \
    dnsquery.h \
    dnsupdate.h \
    dnswindow.h \
    ftp.h \
    http.h \
    httpget.h \
    httppost.h \
    icmp.h \
    mainwindow.h

FORMS += \
    dhcp.ui \
    dhcprequest.ui \
    dnsoptiuni.ui \
    dnsupdate.ui \
    dnswindow.ui \
    ftp.ui \
    http.ui \
    httpget.ui \
    httppost.ui \
    icmp.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
