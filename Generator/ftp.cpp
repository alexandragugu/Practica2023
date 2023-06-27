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
    QString serverIP = "127.0.0.1";
    int serverPort = 14148;

    // Definiți calea și numele fișierului de destinație pe serverul FTP
    QString remoteFilePath = "D:/Practica2023/test_ftp.txt";

    // Setați URL-ul utilizând adresa IP și portul
    QUrl url;
    url.setScheme("ftp");
    url.setHost(serverIP);
    url.setPort(serverPort);
    url.setPath(remoteFilePath);

    // Setăm numele utilizatorului și parola pentru autentificare FTP (dacă este necesar)
    url.setUserName(this->user);
    url.setPassword(this->parola);

    // Definiți calea și numele fișierului local pe care dorim să îl încărcăm
    QString localFilePath = this->cale_sursa;

    // Verificăm dacă fișierul local există și este deschis pentru citire
    QFile file(localFilePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open local file for reading";
    }

    // Realizăm cererea PUT pentru a încărca fișierul
    QNetworkReply *reply = manager.put(QNetworkRequest(url), &file);
    if (reply==nullptr)
        qDebug()<<"Nu a primit reply";
    else
        qDebug()<<"A primit reply";
    // Conectăm semnalul finished() pentru a verifica când transferul este finalizat
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        qDebug()<<"S-a conectat";
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Transfer completed successfully";
        } else {
            qDebug() << "Transfer failed. Error:" << reply->errorString();
        }

        // Închidem fișierul local și închidem aplicația după finalizarea transferului
        file.close();
        //qApp->quit();
    });

    this->close();
}


