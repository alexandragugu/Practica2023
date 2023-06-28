#ifndef DNSOPTIUNI_H
#define DNSOPTIUNI_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class DNSOptiuni;
}

class DNSOptiuni : public QMainWindow
{
protected:
    Q_OBJECT

    QString ip;
    QString domeniu;
    QString packet_type;
    int port;
    QString path;
    QString proxy_ip;
    QString proxy_port;

public:
    DNSOptiuni(QWidget *parent = nullptr);
    //DNSOptiuni(QString type);
    void getType(QString tip){this->packet_type=tip;};
    void getPath(QString cale){ this->path=cale;};
    ~DNSOptiuni();


private slots:

    void on_OK_clicked();

    void on_lineEdit_4_editingFinished();

 //   void on_numarPort_editingFinished();

    void on_ip_proxy_editingFinished();

    void on_port_proxy_editingFinished();

private:
    Ui::DNSOptiuni *ui;
};

#endif // DNSOPTIUNI_H
