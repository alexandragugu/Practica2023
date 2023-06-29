/*#include "httpget.h"
#include "ui_httpget.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QDebug>
#include <QtNetwork/QNetworkProxy>
#include <QUrl>
*/

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
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkProxy>

HttpGet::HttpGet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HttpGet)
{
    ui->setupUi(this);
}
/*
HttpGet::~HttpGet()
{
    delete ui;
}
*/
void HttpGet::on_lineEdit_editingFinished()
{
    QString text=ui->lineEdit->text();
    this->url=text;
}


void HttpGet::on_pushButton_clicked()
{

    QNetworkAccessManager *manager = new QNetworkAccessManager();


    if (this->proxy_ip!="" && this->proxy_port!=0){
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(this->proxy_ip);
        proxy.setPort(this->proxy_port);
        manager->setProxy(proxy);

    }

    QNetworkRequest request;
    request.setUrl(QUrl(this->url));
    this->saveRequest(request,this->url);

    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(this->url)));

    // qDebug()<<"Aici";
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        qDebug()<<"A intrat in connect";
        QByteArray responseData = reply->readAll();
        //qDebug() << responseData;
        //Extragem adresa IP de unde am primit raspunsul
        QHostAddress lAddress = QHostAddress(QHostAddress::LocalHost);
        QString hostIP = lAddress.toString();
        QByteArray sourceIPBytes = reply->rawHeader("X-Reply-Source-IP");
         QString sourceIP= QString::fromUtf8(sourceIPBytes);


         QByteArray decodedData=responseData; // = QByteArray::fromPercentEncoding(responseData);
        QString text = QString::fromUtf8(decodedData);
        QString decodedText = text;
        qDebug()<<decodedText;
        QJsonObject json;
        json["packetType"] = "Response";
        json["sourceIP"] = hostIP;
        json["destinationIP"] = sourceIP;
        json["messageLength"] = decodedData.length();



        QJsonDocument jsonDocument(json);
        QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);


        QFile file(this->path);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << jsonString;
            file.close();
            qDebug() << "Fisierul a fost salvat cu succes.";
        } else {
            qDebug() << "Eroare la salvarea fisierului ";
        }
    });

    // Elibereaza resursele

    this->close();

}


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


    QJsonDocument jsonDocument(requestObject);



    QFile file(this->path);
    if (file.open(QIODevice::Append)) {
        file.write(jsonDocument.toJson());
        file.close();
        qDebug() << "Cererea a fost salvata in fisier";
    } else {
        qDebug() << "Eroare la salvarea cererii in fisier";
    }
}


void HttpGet::on_ip_proxy_editingFinished()
{
    this->proxy_ip=ui->ip_proxy->text();
}


void HttpGet::on_port_proxy_editingFinished()
{
    this->proxy_port=ui->port_proxy->text().toInt();
}

