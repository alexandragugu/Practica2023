
#ifndef DNSQUERY_H
#define DNSQUERY_H

#include "dns.h"
#include <QByteArray>
#include <QDebug>
#include <QString>

class DNSQuery : public DNS
{
protected:
    QString domainIP;
    QString proxy_ip;
    int proxy_port;
    int port;
public:
    DNSQuery(QString domeniu);
    void trimite();
private:
    QByteArray buildDnsQueryPacket(const QString& domainName);
    void savePacket (const QByteArray& packet);
    void savePacketResponse (const QByteArray& packet);
};

#endif // DNSQUERY_H
