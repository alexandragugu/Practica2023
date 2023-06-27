#include "http.h"
#include "ui_http.h"
#include "httpget.h"

HTTP::HTTP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HTTP)
{
    ui->setupUi(this);
}

HTTP::~HTTP()
{
    delete ui;
}

void HTTP::on_pushButton_3_clicked()
{

}


void HTTP::on_pushButton_2_clicked()
{
    HttpGet *nou=new HttpGet();
     nou->show();
}
void HTTP::on_pushButton_clicked()
{
     this->close();
}

