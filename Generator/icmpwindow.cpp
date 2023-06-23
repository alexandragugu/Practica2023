#include "icmpwindow.h"
#include "ui_icmpwindow.h"

ICMPWindow::ICMPWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ICMPWindow)
{
    ui->setupUi(this);
}

ICMPWindow::~ICMPWindow()
{
    delete ui;
}
