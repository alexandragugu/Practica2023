
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dnswindow.h"
#include "http.h"
#include "ftp.h"
#include "icmp.h"
#include "dhcp.h"
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
{
    ui->setupUi(this);
}

/*
MainWindow::~MainWindow()
{
    delete ui;
}
*/

void MainWindow::on_ICMP_clicked()
{
    qDebug("DA");
    if(this->ok==0){
        this->getNumber();
        this->ok++;
    }
    DNSWindow *nou=new DNSWindow();
    nou->getPath(this->path);
    nou->show();

}


void MainWindow::on_pushButton_clicked()
{
    qDebug("HTTP");
    if(this->ok==0){
        this->getNumber();
        this->ok++;
    }
    HTTP *nou=new HTTP();
    nou->getPath(this->path);
    nou->show();

}


void MainWindow::on_pushButton_2_clicked()
{
    if(this->ok==0){
        this->getNumber();
        this->ok++;
    }

    FTP *nou=new FTP();
    nou->getPath(this->path);
    nou->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    if(this->ok==0){
        this->getNumber();
        this->ok++;
    }
    ICMP *nou=new ICMP();
    nou->getPath(this->path);
    nou->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    if(this->ok==0){
        this->getNumber();
        this->ok++;
    }
    DHCP *nou=new DHCP();
    nou->getPath(this->path);
    nou->show();
}

QString MainWindow::getNumber()
{
    QString firstLine;
    QString filePath="D:/Practica2023/numar.txt";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        if (!in.atEnd()) {
            firstLine = in.readLine();
        }
        file.close();
    }
    this->path=this->path+firstLine+".txt";
    qDebug()<<this->path;
    //Scrie iar in fisier
    int number=firstLine.toInt();
    number++;
    qDebug()<<number;
    QFile file2(filePath);
    if (file2.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file2);
        stream << number;
        qDebug()<<"A scris in fisier";
        file2.close();

    } else {
        qDebug() << "Eroare la salvarea fisierului";
    }
    QString trimite;
    return trimite.setNum(number);
}


void MainWindow::on_pushButton_5_clicked()
{
    this->close();
}

