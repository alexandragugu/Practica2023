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

DHCP::~DHCP()
{
    delete ui;
}

void DHCP::on_Discover_clicked()
{
    QUdpSocket socket;
    if (!socket.bind()) {
        qWarning() << "Failed to bind socket:" << socket.errorString();

    }
/*
    // Construim pachetul DHCP
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    // Header DHCP
    out << quint8(0x01);  // Mesaj tip BOOTREQUEST
    out << quint8(0x01);  // Lungimea adresei hardware
    out << quint8(0x06);  // Lungimea adresei IP
    out << quint8(0x00);  // Lungimea clientului hardware
    out << quint32(0x00); // Opțiuni DHCP rezervate

    // Adăugăm opțiunea DHCP Discover
    out << quint8(0x35);  // Codul opțiunii DHCP Discover
    out << quint8(0x01);  // Lungimea opțiunii
    out << quint8(0x01);  // Valoarea opțiunii Discover

    // Trimitem pachetul DHCP la adresa de broadcast
    QNetworkDatagram datagramToSend(datagram, QHostAddress::Broadcast, 67);
    if (!socket.writeDatagram(datagramToSend)) {
        qWarning() << "Failed to send DHCP packet:" << socket.errorString();

    }
*/
    QString proxyAddress = "192.168.1.100";
    int proxyPort = 8080;

    // Construim pachetul DHCP
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    // Header DHCP
    out << quint8(0x01);  // Mesaj tip BOOTREQUEST
    out << quint8(0x01);  // Lungimea adresei hardware
    out << quint8(0x06);  // Lungimea adresei IP
    out << quint8(0x00);  // Lungimea clientului hardware
    out << quint32(0x00); // Opțiuni DHCP rezervate

    // Adăugăm opțiunea DHCP Discover
    out << quint8(0x35);  // Codul opțiunii DHCP Discover
    out << quint8(0x01);  // Lungimea opțiunii
    out << quint8(0x01);  // Valoarea opțiunii Discover

    // Trimitem pachetul DHCP la adresa de broadcast prin intermediul proxy-ului
    QHostAddress proxyHost(proxyAddress);
    QNetworkDatagram datagramToSend(datagram, proxyHost, proxyPort);  // Utilizăm adresa IP și portul proxy-ului în loc de adresa de broadcast
    if (!socket.writeDatagram(datagramToSend)) {
        qWarning() << "Failed to send DHCP packet:" << socket.errorString();
    }

    // Salvăm pachetul DHCP într-un fișier
    QString filePath = "/path/to/file.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << datagram.toHex(' ');  // Salvăm pachetul sub forma de text hexazecimal
        file.close();
    } else {
        qWarning() << "Failed to open file for writing:" << file.errorString();
    }


    // Salvăm pachetul DHCP sub forma unei structuri JSON
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
    // Convertim obiectul JSON într-un document JSON
    QJsonDocument jsonDoc(dhcpPacketJson);

    // Salvăm documentul JSON într-un fișier text
    QString path="D:/Practica2023/dhcp_packet.txt";
    QFile outputFile(path);
    if (outputFile.open(QIODevice::Append | QIODevice::Text)) {
        outputFile.write(jsonDoc.toJson());
        outputFile.close();
        qDebug() << "Pachetul DHCP a fost salvat în fisierul dhcp_packet.txt";
    } else {
        qWarning() << "Nu s-a putut deschide fisierul pentru scriere";
    }

    this->close();
}


void DHCP::on_Request_clicked()
{
    DHCPRequest *nou=new DHCPRequest();
    nou->show();
}

