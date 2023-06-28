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

    quint16 icmpSequence = this->secNr.toInt();

    // Construirea datelor pachetului ICMP
    data.append(char(8)); // Tipul mesajului ICMP (8 pentru cerere Echo)
    data.append(char(0)); // Codul mesajului ICMP
    data.append(QByteArray::fromRawData(reinterpret_cast<const char*>(&icmpID), sizeof(icmpID))); // ID-ul ICMP
    data.append(QByteArray::fromRawData(reinterpret_cast<const char*>(&icmpSequence), sizeof(icmpSequence))); // Nr secv ICMP
    QNetworkDatagram datagram(data, QHostAddress(destinationIP), 0);

    QJsonObject jsonData1;
    jsonData1["icmp_packet"] = QString(data.toHex());  // Convertire pachet hexa
    jsonData1["Destination"] = this->ip;
    jsonData1["id"]=this->id;
    jsonData1["Numar de secventa"]=this->secNr;

    QJsonDocument jsonDoc(jsonData1);
    QByteArray jsonBytes1 = jsonDoc.toJson();


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

        qDebug() << "Răspuns ICMP primit:" << replyData;

        QJsonObject jsonData;
         jsonData["Type"] = "Response";
        jsonData["icmp_packet"] = QString(replyData.toHex());

        QJsonDocument jsonDoc(jsonData);
        QByteArray jsonBytes = jsonDoc.toJson();


            QFile file(this->path);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            file.write(jsonBytes1);
            file.write(jsonBytes);
            file.close();
            qDebug() << "Pachetul ICMP a fost salvat" ;
        } else {
            qWarning() << "Eroare la salvarea pachetului ICMP" ;
        }
    } else {
        qDebug() << "Nu s-a primit raspuns ICMP.";
    }

    this->close();
}

