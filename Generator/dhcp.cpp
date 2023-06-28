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
    out << quint32(0x00); // Opțiuni DHCP rezervate

    // Adăugăm opțiunea DHCP Discover
    out << quint8(0x35);  // Codul opțiunii DHCP Discover
    out << quint8(0x01);  // Lungimea opt
    out << quint8(0x01);  // Valoare Discover

    // Trimitem pachetul DHCP la adresa de broadcast prin intermediul proxy-ului
    QHostAddress proxyHost(proxyAddress);
    QNetworkDatagram datagramToSend(datagram, proxyHost, proxyPort);  //
    if (!socket.writeDatagram(datagramToSend)) {
        qWarning() << "Failed to send DHCP packet:" << socket.errorString();
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
    // Convertim obiectul JSON într-un document JSON
    QJsonDocument jsonDoc(dhcpPacketJson);


    QString path="D:/Practica2023/dhcp_packet.txt";
    QFile outputFile(this->path);
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
    nou->getPath(this->path);
    nou->show();
}

