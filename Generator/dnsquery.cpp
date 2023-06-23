
#include "dnsquery.h"
#include <QCoreApplication>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QHostInfo>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDateTime>
#include <qudpsocket.h>

DNSQuery::DNSQuery(QString domeniu)
{
    this->domeniu=domeniu;
}

void DNSQuery::trimite()
{
    this->getIPAddress();
    qDebug()<<"Adresa ip host:"<<this->HostAddress;
    QString domainName =this->domeniu;


    QHostInfo::lookupHost(domainName, [this](const QHostInfo &hostInfo) {
        qDebug()<<"A trimis";
        if (hostInfo.error() == QHostInfo::NoError) {
            QHostAddress address = hostInfo.addresses().first();
            this->domainIP =address.toString();
            qDebug()<<address;
            QNetworkDatagram datagram;
            datagram.setData("Hello DNS");
            datagram.setDestination(address, 53); // DNS port
            qDebug() << "Packet Data:" << QString::fromLatin1(datagram.data());
            savePacket(datagram.data());


            QUdpSocket socket;
            socket.open(QIODevice::ReadWrite);

            socket.writeDatagram(datagram);

            QObject::connect(&socket, &QUdpSocket::readyRead, [&]() {
                while (socket.hasPendingDatagrams()) {
                    QNetworkDatagram receivedDatagram = socket.receiveDatagram();
                   qDebug()<<QString::fromLatin1(datagram.data());
                    savePacketResponse(datagram.data());
                }
                QCoreApplication::quit();
            });

        } else {
            qDebug() << "DNS lookup failed:" << hostInfo.errorString();
            QCoreApplication::quit();
        }
    });

}



void DNSQuery::savePacket (const QByteArray &packet)
{
    QJsonObject jsonObject;
    jsonObject["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonObject["Source"] = this->HostAddress;
    jsonObject["Destination"] = this->domainIP;
    jsonObject["packet"] = QString::fromLatin1(packet.toHex());

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();
    QString path="D:/Practica2023/dns_query.txt";
    QFile file(path);
    if (file.open(QIODevice::Append)){
        file.write(jsonData);
        file.close();
        qDebug() << "DNS query and response saved to dns_query.json";
    } else {
        qDebug() << "Failed to save DNS query and response.";
    }
}


void DNSQuery::savePacketResponse(const QByteArray &packet)
{
    QJsonObject jsonObject;
    this->getIPAddress();
    jsonObject["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonObject["Source"] =this->domainIP;
    jsonObject["Destination"] = this->HostAddress;
    jsonObject["packet"] = QString::fromLatin1(packet.toHex());

    // jsonObject["response"] = QString::fromLatin1(response.toHex());

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();
    QString path="D:/Practica2023/dns_query.txt";
    QFile file(path);
    if (file.open(QIODevice::Append)){
        file.write(jsonData);
        file.close();
        qDebug() << "DNS query and response saved to dns_query.json";
    } else {
        qDebug() << "Failed to save DNS query and response.";
    }
}

