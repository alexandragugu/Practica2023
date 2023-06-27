#ifndef DNSUPDATE_H
#define DNSUPDATE_H

#include <QMainWindow>
#include <QString>
#include "dns.h"

namespace Ui {
class DNSUpdate;
}

class DNSUpdate : public QMainWindow,
                public DNS
{
    Q_OBJECT
protected:
    QString adresaIP="127.0.0.1";
    QString nr_port;

public:
    explicit DNSUpdate(QWidget *parent = nullptr);
    ~DNSUpdate();

private slots:
    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::DNSUpdate *ui;
};

#endif // DNSUPDATE_H
