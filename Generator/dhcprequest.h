#ifndef DHCPREQUEST_H
#define DHCPREQUEST_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class DHCPRequest;
}

class DHCPRequest : public QMainWindow
{
    Q_OBJECT
    QString ip;
    QString proxy_ip="";
    int proxy_port=0;
public:
    explicit DHCPRequest(QWidget *parent = nullptr);
    ~DHCPRequest();

private slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

    void on_ip_proxy_editingFinished();

    void on_port_proxy_editingFinished();

private:
    Ui::DHCPRequest *ui;
};

#endif // DHCPREQUEST_H
