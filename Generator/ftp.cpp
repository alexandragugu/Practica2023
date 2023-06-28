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

FTP::FTP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FTP)
{
    ui->setupUi(this);
}

FTP::~FTP()
{
    delete ui;
}

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


/*void FTP::on_pushButton_clicked()
{
    //UPLOAD
    QNetworkAccessManager manager;

    // Definiți adresa și calea către fișierul de destinație pe serverul FTP

    QUrl url("ftp://cale_destinatie/fisier_ftp.txt");

    // Setăm numele utilizatorului și parola pentru autentificare FTP (dacă este necesar)
    url.setUserName(this->user);
    url.setPassword(this->parola);

    // Definim fișierul local pe care dorim să-l încărcăm
    QString localFilePath =this->cale_sursa;

    QFile file(localFilePath);

    // Verificăm dacă fișierul local există și este deschis pentru citire
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open local file for reading";
    }

    // Realizăm cererea PUT pentru a încărca fișierul
    QNetworkReply *reply = manager.put(QNetworkRequest(url), &file);

    // Conectăm semnalul finished() pentru a verifica când transferul este finalizat
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Transfer completed";
            QByteArray responseData = reply->readAll();

            // Creăm structura JSON
            QJsonObject jsonObject;
            jsonObject["url"] = url.toString();
            jsonObject["file_content"] = QString(responseData);

            // Serializăm structura JSON
            QJsonDocument jsonDocument(jsonObject);
            QByteArray jsonBytes = jsonDocument.toJson();

            // Scriem structura JSON în fișierul text
            QFile jsonFile("D:/Practica2023/out.txt");
            if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                jsonFile.write(jsonBytes);
                jsonFile.close();
                qDebug() << "JSON data saved to output.txt";
            } else {
                qDebug() << "Failed to open output.txt for writing";
            }
        } else {
            qDebug() << "Transfer failed. Error:" << reply->errorString();
        }

        // Închidem fișierul local și închidem aplicația după finalizarea transferului
        file.close();
        qApp->quit();
    });

    this->close();
}
*/

void FTP::on_pushButton_clicked()
{
    QNetworkAccessManager manager;
    qDebug()<<"A intart in FTP";
    // Definiți adresa IP și portul serverului FTP
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
        //qApp->quit();
    });

    this->close();
}



void FTP::on_lineEdit_6_editingFinished()
{
    this->port_number=ui->lineEdit_6->text().toInt();
}

