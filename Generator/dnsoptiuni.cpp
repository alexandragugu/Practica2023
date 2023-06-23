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
        packet->trimite();
    }
    this->close();
}


/*void DNSOptiuni::on_lineEdit_editingFinished()
{
    QString text = ui->lineEdit->text();
    this->ip=text;
    text="1->"+text;
    qDebug()<<text;
}
*/


void DNSOptiuni::on_lineEdit_4_editingFinished()
{
    QString text = ui->lineEdit_4->text();
    this->domeniu=text;
    text="2->"+text;
    qDebug()<<text;
}

/*void DNSOptiuni::on_lineEdit_4_editingFinished()
{
    QString text = ui->lineEdit->text();
    this->domeniu=text;
    text="3->"+text;
    qDebug()<<text;
}


void DNSOptiuni::on_lineEdit_2_editingFinished()
{
    QString text = ui->lineEdit->text();
    this->info=text;
    text="4->"+text;
    qDebug()<<text;
}


void DNSOptiuni::on_lineEdit_5_editingFinished()
{
    QString text = ui->lineEdit->text();
    this->clasa=text;
    text="5->"+text;
    qDebug()<<text;
}
*/




