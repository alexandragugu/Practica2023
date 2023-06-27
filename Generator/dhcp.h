#ifndef DHCP_H
#define DHCP_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class DHCP;
}

class DHCP : public QMainWindow
{
    Q_OBJECT
protected:
    QString ip_proxy;
    int proxy_port;
public:
    explicit DHCP(QWidget *parent = nullptr);
    ~DHCP();

private slots:
    void on_Discover_clicked();

    void on_Request_clicked();

private:
    Ui::DHCP *ui;
};

#endif // DHCP_H
