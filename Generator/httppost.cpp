#include "httppost.h"
#include "ui_httppost.h"
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QCoreApplication>
//#include <QMailMessage>
//#include <QMailTransport>


HTTPPost::HTTPPost(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HTTPPost)
{
    ui->setupUi(this);
}

HTTPPost::~HTTPPost()
{
    delete ui;
}

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
    /*
    QMailMessage message;
    message.setSender(from);
    message.setTo(to);
    message.setSubject(data);
    message.setBody("corp mail");

    QMailTransport* transport = QMailTransport::create("smtp");
    transport->connectToHost();

    if (transport->state() == QMailTransport::Disconnected) {
        qDebug() << "Eroare la conectarea la serverul SMTP.";
        return;
    }

    if (!transport->sendMessages(QList<QMailMessage>() << message)) {
        qDebug() << "Eroare la trimiterea e-mailului.";
    }

    transport->disconnectFromHost();
    transport->deleteLater();
}
*/
    this->close();
}

void HTTPPost::readData()
{
    QString path="D:/Practica2023/"+this->sourcefile;
    QFile file(path);

    if (file.open(QIODevice::ReadOnly)) {
        this->data = file.readAll();
        file.close();

        qDebug() << "Continutul fisierului:";
        qDebug() << data;
    } else {
        qDebug() << "Nu s-a putut deschide fisierul!";
    }

}

