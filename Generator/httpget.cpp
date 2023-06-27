#include "httpget.h"
#include "ui_httpget.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QDebug>


HttpGet::HttpGet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HttpGet)
{
    ui->setupUi(this);
}

HttpGet::~HttpGet()
{
    delete ui;
}

void HttpGet::on_lineEdit_editingFinished()
{
    QString text=ui->lineEdit->text();
    this->url=text;
}


void HttpGet::on_pushButton_clicked()
{

    QNetworkAccessManager* manager = new QNetworkAccessManager();

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    this->saveRequest(request,url);

    QNetworkReply* reply = manager->get(request);

    QHostAddress lAddress = QHostAddress(QHostAddress::LocalHost);
    QString hostIP = lAddress.toString();
   // QString sourceIP;
   // QString decodedText;
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        // Procesează răspunsul HTTP
        QByteArray responseData = reply->readAll();

        //Extragem adresa IP de unde am primit raspunsul
        QByteArray sourceIPBytes = reply->rawHeader("X-Reply-Source-IP");
         QString sourceIP= QString::fromUtf8(sourceIPBytes);

       // qDebug() << responseData.toUtf8();
        QByteArray decodedData = QByteArray::fromPercentEncoding(responseData);
        QString text = QString::fromUtf8(decodedData);
        QString decodedText = text;
        qDebug()<<decodedText;
        QJsonObject json;
        json["packetType"] = "Response";
        json["sourceIP"] = hostIP;
        json["destinationIP"] = sourceIP;
        json["messageLength"] = decodedData.length() ;

        // Converteste obiectul JSON in șir de caractere
        QString path="D:/Practica2023/http_get.txt";
        QJsonDocument jsonDocument(json);
        QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);

        // Salvează șirul JSON într-un fișier text
        QFile file(path);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << jsonString;
            file.close();
            qDebug() << "Fisierul http_get.txt a fost salvat cu succes.";
        } else {
            qDebug() << "Eroare la salvarea fisierului http_get.txt.";
        }
      });
    // Elibereaza resursele
    reply->deleteLater();
    manager->deleteLater();


    this->close();

}

        /*
// -------------------------------------------------------------------
        // Manipulează datele primite aici

        QJsonDocument jsonDocument = QJsonDocument::fromJson(decodedData);
        QJsonParseError jsonError;
        QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);
        if (jsonError.error != QJsonParseError::NoError) {
            // Parsarea JSON a eșuat
            qDebug() << "Eroare la parsarea JSON:" << jsonError.errorString();
            qDebug() << "La poziția:" << jsonError.offset;
        } else {
            // Parsarea JSON a reușit
            qDebug() << "JSON parsat cu succes.";

            // Continuă manipularea datelor JSON aici
        }

        // Verifică dacă parsarea JSON a fost reușită
        if (jsonDocument.isNull()){
            qDebug()<<"E GOL";
        }else {
        if (!jsonDocument.isNull()) {
            // Converteste JSON-ul intr-un string formatat pentru a fi salvat in fisier

            QString path="D:/Practica2023/httpget.txt";
            // Deschide fisierul pentru scriere
            QFile file(path);

            if (file.open(QIODevice::Append)) {
                QTextStream stream(&file);
                stream << jsonString;
                file.close();
                qDebug() << "Pachetul a fost salvat cu succes în fisierul JSON.";
            } else {
                qDebug() << "Eroare la salvarea pachetului în fisierul JSON.";
            }
        } else {
            qDebug() << "Eroare la parsarea pachetului JSON.";
        }
        }
//--------------------------------------------------------------------------------------------
*/


void HttpGet::saveRequest(QNetworkRequest request, QString url_addr)
{
    QJsonObject requestObject;
    requestObject["url"] = request.url().toString();
    requestObject["method"] = request.attribute(QNetworkRequest::CustomVerbAttribute).toString();
    QList<QByteArray> headerList = request.rawHeaderList();
    QList<QByteArray> headers = request.rawHeaderList();
    QJsonArray headersArray;
    for (const QByteArray& header : headers) {
        headersArray.append(QString(header));
    }
    requestObject["headers"] = headersArray;

    // Convertim obiectul JSON într-un document JSON
    QJsonDocument jsonDocument(requestObject);

    // Salvăm documentul JSON într-un fișier text
    QString path="D:/Practica2023/httpget.txt";
    QFile file(path);
    if (file.open(QIODevice::Append)) {
        file.write(jsonDocument.toJson());
        file.close();
        qDebug() << "Cererea a fost salvată în fișierul request.json.";
    } else {
        qDebug() << "Eroare la salvarea cererii în fișierul request.json.";
    }
}
/*
void HttpGet::savepacket(QString url, QString data)
{
    QJsonObject packetObject;
    packetObject["url"] = url;
    packetObject["responseData"] =data;

    // Creează documentul JSON
    QJsonDocument jsonDoc(packetObject);
    QString path="D:/Practica2023/httpget.txt";
    // Deschide fișierul pentru scriere
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        // Scrie documentul JSON în fișier
      file.write(jsonDoc.toJson());

        // Închide fișierul
        file.close();
    }
}
*/
