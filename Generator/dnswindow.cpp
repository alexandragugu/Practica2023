#include "dnswindow.h"
#include "ui_dnswindow.h"
#include <QLineEdit>
#include "dnsoptiuni.h"
#include "dnsupdate.h"

DNSWindow::DNSWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DNSWindow)
{
    ui->setupUi(this);

}

DNSWindow::~DNSWindow()
{
    delete ui;
}

void DNSWindow::on_pushButton_clicked()
{
    DNSOptiuni *optiuni=new DNSOptiuni();
    optiuni->getType("Query");
    optiuni->show();

}


void DNSWindow::on_pushButton_2_clicked()
{
    DNSOptiuni *optiuni=new DNSOptiuni();
    optiuni->show();
}


void DNSWindow::on_pushButton_3_clicked()
{
    DNSOptiuni *optiuni=new DNSOptiuni();
    optiuni->show();
}


void DNSWindow::on_pushButton_4_clicked()
{
    DNSUpdate *optiuni= new DNSUpdate();
    optiuni->show();
}


void DNSWindow::on_pushButton_5_clicked()
{
    this->close();
}

