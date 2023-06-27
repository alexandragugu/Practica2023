#include "icmp.h"
#include "ui_icmp.h"
#include <QCoreApplication>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

ICMP::ICMP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ICMP)
{
    ui->setupUi(this);
}

ICMP::~ICMP()
{
    delete ui;
}

void ICMP::on_lineEdit_editingFinished()
{
    this->ip=ui->lineEdit->text();
}


void ICMP::on_lineEdit_2_editingFinished()
{
    this->id=ui->lineEdit_2->text();
}


void ICMP::on_lineEdit_3_editingFinished()
{
    this->secNr=ui->lineEdit_3->text();
}


void ICMP::on_pushButton_clicked()
{
    QUdpSocket socket;
    socket.open(QIODevice::ReadWrite);
    QString destinationIP = this->ip;

    QByteArray data;

    quint16 icmpID = this->id.toInt();
        //this->id.toInt();
        //1234; // ID-ul ICMP
    quint16 icmpSequence = this->secNr.toInt();
        //1; // Numărul de secvență ICMP

    // Construirea datelor pachetului ICMP
    data.append(char(8)); // Tipul mesajului ICMP (8 pentru cerere Echo)
    data.append(char(0)); // Codul mesajului ICMP
    data.append(QByteArray::fromRawData(reinterpret_cast<const char*>(&icmpID), sizeof(icmpID))); // ID-ul ICMP
    data.append(QByteArray::fromRawData(reinterpret_cast<const char*>(&icmpSequence), sizeof(icmpSequence))); // Numărul de secvență ICMP
    data.append("Hello, ICMP!"); // Date suplimentare

    QNetworkDatagram datagram(data, QHostAddress(destinationIP), 0);

    // Trimiterea pachetului ICMP
   // socket.writeDatagram(datagram);
    if (socket.writeDatagram(datagram) == -1) {
        qDebug() << "Eroare la trimiterea pachetului ICMP.";
    } else {
        qDebug() << "Pachetul ICMP a fost trimis cu succes.";
    }
    QNetworkDatagram replyDatagram;
    if (socket.waitForReadyRead()) {
        replyDatagram = socket.receiveDatagram();
        QByteArray replyData = replyDatagram.data();
        // Procesați și afișați răspunsul ICMP aici
        qDebug() << "Răspuns ICMP primit:" << replyData;
                // Salvarea pachetului creat într-o structură JSON
        QJsonObject jsonData;
        jsonData["icmp_packet"] = QString(replyData.toHex());  // Convertirea pachetului în format hexadecimal
        jsonData["Destination"] = this->ip;
        jsonData["id"]=this->id;
        jsonData["Numar de secventa"]=this->secNr;
        // Convertirea structurii JSON în format text
        QJsonDocument jsonDoc(jsonData);
        QByteArray jsonBytes = jsonDoc.toJson();

        QString path="D:/Practica2023/icmp_packet.txt";
        QString fileName = "icmp_packet.json";
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(jsonBytes);
            file.close();
            qDebug() << "Pachetul ICMP a fost salvat în fișierul" << fileName;
        } else {
            qWarning() << "Eroare la salvarea pachetului ICMP în fișierul" << fileName;
        }
    } else {
        qDebug() << "Nu s-a primit răspuns ICMP.";
    }

    this->close();
}

