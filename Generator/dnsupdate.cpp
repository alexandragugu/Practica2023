#include "dnsupdate.h"
#include "ui_dnsupdate.h"
#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

DNSUpdate::DNSUpdate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DNSUpdate)
{

    ui->setupUi(this);
}

DNSUpdate::~DNSUpdate()
{
    delete ui;
}

void DNSUpdate::on_lineEdit_editingFinished()
{
    QString text = ui->lineEdit->text();
    this->adresaIP=text;
}


void DNSUpdate::on_lineEdit_2_editingFinished()
{
    QString text=ui->lineEdit_2->text();
    this->nr_port=text;
}


void DNSUpdate::on_pushButton_clicked()
{
    QHostAddress dnsServerAddress(this->adresaIP);
    quint16 dnsPort = this->nr_port.toInt();


    QUdpSocket socket;


    QByteArray dnsUpdatePacket;

    dnsUpdatePacket.append('\x00');  // Opcode si alte setari
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x00');  // Numarul de intrebari
    dnsUpdatePacket.append('\x01');  // Numarul de inregistrari resurse adaugate
    dnsUpdatePacket.append('\xC0');  // Nume de domeniu: Pointer către numele de domeniu în întrebare
    dnsUpdatePacket.append('\x0C');
    dnsUpdatePacket.append('\x00');  // tip inregistrare: A =ip
    dnsUpdatePacket.append('\x01');
    dnsUpdatePacket.append('\x00');  // Clasa de inregistrare IN (Internet)
    dnsUpdatePacket.append('\x01');  //
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x04');  // Lungimea datelor
    QByteArray ip;
    if (this->proxy_ip!=""){
      ip =this->adresaIP.toUtf8().toHex();
    }
    else{
      ip=this->adresaIP.toUtf8().toHex();
    }
    dnsUpdatePacket.append(ip);
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x01');


    socket.writeDatagram(dnsUpdatePacket, dnsServerAddress, dnsPort);

    QJsonObject jsonData;
    this->getIPAddress();
    jsonData["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonData["Source"] =this->HostAddress;
    jsonData["Destination"] =this->adresaIP;
    jsonData["dns_update_packet"] = QString::fromLatin1(dnsUpdatePacket.toHex());

    QJsonDocument jsonDoc(jsonData);
    QByteArray jsonBytes = jsonDoc.toJson();


    // Salvare in fisier
    QString path="D:/Practica2023/dns_packet.txt";
    QFile file(this->path);
    if (file.open(QIODevice::Append)) {
        file.write(jsonBytes);
        file.close();
        qDebug() << "Pachetul DNS a fost salvat in fisierul dns_packet.txt";
    } else {
        qWarning() << "Eroare la deschiderea fisierului pentru scriere.";
    }
    this->close();
}


void DNSUpdate::on_ip_proxy_editingFinished()
{
    this->proxy_ip=ui->ip_proxy->text();
}



void DNSUpdate::on_lineEdit_4_editingFinished()
{
    this->proxy_port=ui->port_proxy->text().toInt();
}

