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

    dnsUpdatePacket.append('\x00');  // Opcode și alte setări
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x00');  // Numărul de întrebări
    dnsUpdatePacket.append('\x01');  // Numărul de înregistrări în secțiunea de resurse adăugate
    dnsUpdatePacket.append('\xC0');  // Nume de domeniu: Pointer către numele de domeniu în întrebare
    dnsUpdatePacket.append('\x0C');
    dnsUpdatePacket.append('\x00');  // Tipul de înregistrare: A (adresă IP)
    dnsUpdatePacket.append('\x01');
    dnsUpdatePacket.append('\x00');  // Clasa de înregistrare: IN (Internet)
    dnsUpdatePacket.append('\x01');  // Time-To-Live (TTL) pentru înregistrare (valoare de exemplu)
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x04');  // Lungimea datelor de înregistrare: 4 octeți (adresă IP)
    QByteArray ip=this->adresaIP.toUtf8().toHex();
    dnsUpdatePacket.append(ip);  // Adresă IP: 127.0.0.1
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x00');
    dnsUpdatePacket.append('\x01');

    // Trimitere pachet DNS update către serverul DNS
    socket.writeDatagram(dnsUpdatePacket, dnsServerAddress, dnsPort);

    QJsonObject jsonData;
    this->getIPAddress();
    jsonData["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonData["Source"] =this->HostAddress;
    jsonData["Destination"] =this->adresaIP;
    jsonData["dns_update_packet"] = QString::fromLatin1(dnsUpdatePacket.toHex());  // Salvează pachetul DNS ca bază64

    // Convertirea structurii JSON în format text
    QJsonDocument jsonDoc(jsonData);
    QByteArray jsonBytes = jsonDoc.toJson();


    // Salvare in fisier
    QString path="D:/Practica2023/dns_packet.txt";
    QFile file(path);
    if (file.open(QIODevice::Append)) {
        file.write(jsonBytes);
        file.close();
        qDebug() << "Pachetul DNS a fost salvat in fisierul dns_packet.txt";
    } else {
        qWarning() << "Eroare la deschiderea fisierului pentru scriere.";
    }
    this->close();
}

