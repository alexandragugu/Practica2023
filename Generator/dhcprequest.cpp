#include "dhcprequest.h"
#include "ui_dhcprequest.h"
#include <QCoreApplication>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUdpSocket>
#include <QDataStream>
#include <QDebug>
#include <QNetworkDatagram>

DHCPRequest::DHCPRequest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DHCPRequest)
{
    ui->setupUi(this);
}

DHCPRequest::~DHCPRequest()
{
    delete ui;
}

void DHCPRequest::on_lineEdit_editingFinished()
{
    this->ip=ui->lineEdit->text();
}


void DHCPRequest::on_pushButton_clicked()
{

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
    out << quint32(0x00); // Opțiuni DHCP rezervate

    // Adăugăm opțiunea DHCP Request
    out << quint8(0x35);  // Codul DHCP Request
    out << quint8(0x01);  // Lungime
    out << quint8(0x03);  // Valoarea Request

    if(this->ip!="" && this->proxy_port!=0)
    {
        out << quint8(0x36);  // Codul DHCP Proxy
        out << quint8(0x04);  // Lungimea
        out << quint32(QHostAddress(this->proxy_ip).toIPv4Address());
    }
    else{

    // Trimitem pachetul DHCP Request la adresa de broadcast
    QNetworkDatagram datagramToSend(datagram, QHostAddress::Broadcast, 67);
    if (!socket.writeDatagram(datagramToSend)) {
        qWarning() << "Failed to send DHCP Request packet:" << socket.errorString();

    }
    }

    // Salvăm pachetul DHCP sub forma unei structuri JSON
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

    QString path="D:/Practica2023/dhcp_packet.txt";
    QFile file(path);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        file.write(jsonDocument.toJson());
        file.close();
        qDebug() << "Pachetul DHCP a fost salvat";
    } else {
        qWarning() << "Nu s-a putut deschide";
    }
    socket.close();
    this->close();
}


void DHCPRequest::on_ip_proxy_editingFinished()
{
    this->proxy_ip=ui->ip_proxy->text();
}


void DHCPRequest::on_port_proxy_editingFinished()
{
    this->proxy_port=ui->port_proxy->text().toInt();
}

