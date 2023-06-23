
#ifndef DNS_H
#define DNS_H
#include <QString>




class DNS
{
protected:
    QString HostAddress;
    QString adresaIP;
    QString port;
    QString domeniu;
    QString typeinfo;
    QString infoclass;

    void getInfo(QString data);
    QString generateRandomIP();

public:
    virtual void trimite()=0;
    void getIPAddress();
};

#endif // DNS_H
