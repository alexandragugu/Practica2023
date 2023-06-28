
#include "dns.h"
#include <QRandomGenerator>
#include <QCoreApplication>
#include <QHostInfo>
#include <QDebug>


QString DNS::generateRandomIP()
{
    QString ipAddress;
    for (int i = 0; i < 4; ++i) {
        if (i > 0)
            ipAddress.append(".");
        ipAddress.append(QString::number(QRandomGenerator::global()->bounded(256)));
    }
    return ipAddress;
}

void DNS::trimite()
{

}

void DNS::getIPAddress()
{
    QString localHostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> ipAddresses = hostInfo.addresses();


    for (const QHostAddress& ip : ipAddresses) {
        if (ip.protocol() == QAbstractSocket::IPv4Protocol && !ip.isLoopback()) {
            this->HostAddress=ip.toString();
            qDebug() << "Adresa IP:" << ip.toString();
            break;
        }
    }
}
