#include "dnsoptiuni.h"
#include "ui_dnsoptiuni.h"
#include <QDebug>
#include <QRandomGenerator>
#include <dnsquery.h>

DNSOptiuni::DNSOptiuni(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DNSOptiuni)
{
    ui->setupUi(this);
}

DNSOptiuni::~DNSOptiuni()
{
    delete ui;
}


void DNSOptiuni::on_OK_clicked()
{

    if (this->packet_type=="Query"){
        DNSQuery *packet=new DNSQuery(this->domeniu);
        packet->getPath(this->path);
        packet->trimite();
    }
    this->close();
}



void DNSOptiuni::on_lineEdit_4_editingFinished()
{
    QString text = ui->lineEdit_4->text();
    this->domeniu=text;
    text="2->"+text;
    qDebug()<<text;
}



void DNSOptiuni::on_ip_proxy_editingFinished()
{
    this->proxy_ip=ui->ip_proxy->text();
}


void DNSOptiuni::on_port_proxy_editingFinished()
{
    this->proxy_port=ui->port_proxy->text();
}

