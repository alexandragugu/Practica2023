
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dnswindow.h"



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

