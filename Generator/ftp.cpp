#include "ftp.h"
#include "ui_ftp.h"
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>

FTP::FTP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FTP)
{
    ui->setupUi(this);
}
/*
FTP::~FTP()
{
    delete ui;
}
*/

void FTP::on_lineEdit_editingFinished()
{
    this->adresaServer=ui->lineEdit->text();
}


void FTP::on_lineEdit_2_editingFinished()
{
    this->user=ui->lineEdit_2->text();
}


void FTP::on_lineEdit_3_editingFinished()
{
    this->parola=ui->lineEdit_3->text();
}


void FTP::on_lineEdit_4_editingFinished()
{
    this->cale_sursa=ui->lineEdit_4->text();
}


void FTP::on_lineEdit_5_editingFinished()
{
    this->cale_destinatie=ui->lineEdit_5->text();
}


void FTP::on_pushButton_clicked()
{
    QNetworkAccessManager manager;
    qDebug()<<"A intart in FTP";
    if(this->adresaServer==""){
        this->adresaServer=this->generateRamdomIp();
    }
    QString serverIP = this->adresaServer;
    int serverPort = this->port_number;


    QString remoteFilePath = "D:/Practica2023/afisare.txt";

    QUrl url;
    url.setScheme("ftp");
    url.setHost(serverIP);
    url.setPort(serverPort);
    url.setUserName(this->user);
    url.setPassword(this->parola);
    url.setPath(remoteFilePath);


   // QString localFilePath = "D:/Practica2023/afisare.txt";

    QString localFilePath = this->cale_sursa;


    QFile file(localFilePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open local file for reading";
    }

    QNetworkReply *reply = manager.put(QNetworkRequest(url), &file);


    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        qDebug()<<"S-a conectat";
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Transfer completed successfully";
        } else {
            qDebug() << "Transfer failed. Error:" << reply->errorString();
        }

        file.close();

    });

    this->close();
}


void FTP::on_lineEdit_6_editingFinished()
{
    this->port_number=ui->lineEdit_6->text().toInt();
}

QString FTP::generateRamdomIp()
{
    QString ipAddress;
    for (int i = 0; i < 4; ++i) {
        if (i > 0)
            ipAddress.append(".");
        ipAddress.append(QString::number(QRandomGenerator::global()->bounded(256)));
    }
    return ipAddress;
}

