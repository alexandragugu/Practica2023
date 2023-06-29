
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
    QString path;
    QString proxy_ip;
    int proxy_port;

    void getInfo(QString data);
    QString generateRandomIP();

public:
   void trimite();
   void getIPAddress();
   void getPath(QString cale){ this->path=cale;};
};

#endif // DNS_H
