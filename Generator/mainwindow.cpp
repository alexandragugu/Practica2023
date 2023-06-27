
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dnswindow.h"
#include "http.h"
#include "ftp.h"
#include "icmp.h"
#include "dhcp.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ICMP_clicked()
{
    qDebug("DA");
    DNSWindow *nou=new DNSWindow();
    nou->show();

}


void MainWindow::on_pushButton_clicked()
{
    qDebug("HTTP");
    HTTP *nou=new HTTP();
    nou->show();

}


void MainWindow::on_pushButton_2_clicked()
{
    FTP *nou=new FTP();
    nou->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    ICMP *nou=new ICMP();
    nou->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    DHCP *nou=new DHCP();
    nou->show();
}

