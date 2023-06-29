#include "httppost.h"
#include "ui_httppost.h"
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QCoreApplication>
#include <QtNetwork>


HTTPPost::HTTPPost(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HTTPPost)
{
    ui->setupUi(this);
}
/*
HTTPPost::~HTTPPost()
{
    delete ui;
}
*/

void HTTPPost::on_lineEdit_editingFinished()
{
    this->url=ui->lineEdit->text();
}


void HTTPPost::on_lineEdit_2_editingFinished()
{
    this->sourcefile=ui->lineEdit_2->text();
}


void HTTPPost::on_pushButton_clicked()
{
    QNetworkAccessManager manager;

    // Crearea cererii HTTP
    QNetworkRequest request(QUrl(this->url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Crearea datelor care trebuie trimise
    this->readData();
    QByteArray postData=this->data;
   // postData.append("param1=value1");
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


    QNetworkReply *reply = manager.post(request, postData);


    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {

            QByteArray response = reply->readAll();
            qDebug() << "Raspuns:" << response;
        } else {

            qDebug() << "Eroare:" << reply->errorString();
        }

    });

    this->close();
}

void HTTPPost::readData()
{
    QString path=this->sourcefile;
    QFile file(this->path);

    if (file.open(QIODevice::ReadOnly)) {
        this->data = file.readAll();
        file.close();

        qDebug() << "Continutul fisierului:";
        qDebug() << data;
    } else {
        qDebug() << "Nu s-a putut deschide fisierul!";
    }

}

