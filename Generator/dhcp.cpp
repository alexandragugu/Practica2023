#include "dhcp.h"
#include "ui_dhcp.h"
#include "dhcprequest.h"
#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

DHCP::DHCP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DHCP)
{
    ui->setupUi(this);
}

/*
DHCP::~DHCP()
{
    delete ui;
}
*/

void DHCP::on_Discover_clicked()
{
    QUdpSocket socket;
    if (!socket.bind()) {
        qWarning() << "Failed to bind socket:" << socket.errorString();

    }
    QString proxyAddress = this->ip_proxy;
    int proxyPort = this->proxy_port;

    // Construim pachetul DHCP
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    // Header DHCP
    out << quint8(0x01);  // Mesaj tip BOOTREQUEST
    out << quint8(0x01);  // Lungimea adresei hardware
    out << quint8(0x06);  // Lungimea adresei IP
    out << quint8(0x00);  // Lungimea clientului hardware
    out << quint32(0x00); // Optiuni DHCP rezervate


    out << quint8(0x35);  // Codul optiunii DHCP Discover
    out << quint8(0x01);  // Lungimea opt
    out << quint8(0x01);  // Valoare Discover

    // Trimitem pachetul DHCP la adresa de broadcast prin intermediul proxy-ului
    if(this->ip_proxy!="" && this->proxy_port!=0){
        QHostAddress proxyHost(proxyAddress);
        QNetworkDatagram datagramToSend(datagram, proxyHost, proxyPort);  //
        if (!socket.writeDatagram(datagramToSend)) {
            qWarning() << "Failed to send DHCP packet:" << socket.errorString();
        }

    }else {
         QNetworkDatagram datagramToSend(datagram, QHostAddress::Broadcast, 67);
        if (!socket.writeDatagram(datagramToSend)) {
            qWarning() << "Failed to send DHCP packet:" << socket.errorString();
        }
    }


    QFile file(this->path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << datagram.toHex(' ');  // Salvam pachetul sub forma de text hexazecimal
        file.close();
    } else {
        qWarning() << "Failed to open file for writing:" << file.errorString();
    }



    QJsonObject dhcpPacketJson;
    dhcpPacketJson["MessageType"] = 0x01;
    dhcpPacketJson["HardwareAddressLength"] = 0x01;
    dhcpPacketJson["ClientHardwareLength"] = 0x00;
    dhcpPacketJson["ReservedOptions"] = 0x00;

    QJsonObject dhcpDiscoverOption;
    dhcpDiscoverOption["Code"] = 0x35;
    dhcpDiscoverOption["Length"] = 0x01;
    dhcpDiscoverOption["Value"] = 0x01;
    dhcpPacketJson["DHCPDiscoverOption"] = dhcpDiscoverOption;

    QJsonDocument jsonDoc(dhcpPacketJson);


    QFile outputFile(this->path);
    if (outputFile.open(QIODevice::Append | QIODevice::Text)) {
        outputFile.write(jsonDoc.toJson());
        outputFile.close();
        qDebug() << "Pachetul DHCP a fost salvat ";
    } else {
        qWarning() << "Nu s-a putut deschide fisierul pentru scriere";
    }

    this->close();
}


void DHCP::on_Request_clicked()
{
   // DHCPRequest *nou=new DHCPRequest();
    //nou->getPath(this->path);
   // nou->show();
    QUdpSocket socket;
    if (!socket.bind()) {
        qWarning() << "Failed to bind socket:" << socket.errorString();

    }

    // Construim pachetul DHCP Request
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    // Header DHCP
    out << quint8(0x01);  // Mesaj tip BOOTREQUEST
    out << quint8(0x01);  // Lungimea adresei hardware
    out << quint8(0x06);  // Lungimea adresei IP
    out << quint8(0x00);  // Lungimea clientului hardware
    out << quint32(0x00); // Optiuni DHCP rezervate

    // Adaugam optiunea DHCP Request
    out << quint8(0x35);  // Codul DHCP Request
    out << quint8(0x01);  // Lungime
    out << quint8(0x03);  // Valoarea Request

    // Trimitem pachetul DHCP Request la adresa de broadcast
    QNetworkDatagram datagramToSend(datagram, QHostAddress::Broadcast, 67);
    if (!socket.writeDatagram(datagramToSend)) {
        qWarning() << "Failed to send DHCP Request packet:" << socket.errorString();

    }


    // Salvam pachetul DHCP sub forma unei structuri JSON
    QJsonObject dhcpPacketJson;
    dhcpPacketJson["MessageType"] = 0x01;
    dhcpPacketJson["HardwareAddressLength"] = 0x01;
    dhcpPacketJson["IPAddressLength"] = 0x06;
    dhcpPacketJson["ClientHardwareLength"] = 0x00;
    dhcpPacketJson["ReservedOptions"] = 0x00;

    QJsonObject dhcpRequestOption;
    dhcpRequestOption["Code"] = 0x35;
    dhcpRequestOption["Length"] = 0x01;
    dhcpRequestOption["Value"] = 0x03;
    dhcpPacketJson["DHCPRequestOption"] = dhcpRequestOption;


    QJsonDocument jsonDocument(dhcpPacketJson);


    QFile file(this->path);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        file.write(jsonDocument.toJson());
        file.close();
        qDebug() << "Pachetul DHCP a fost salvat";
    } else {
        qWarning() << "Nu s-a putut deschide";
    }
    socket.close();
}


void DHCP::on_Back_clicked()
{
    this->close();
}

