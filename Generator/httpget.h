#ifndef HTTPGET_H
#define HTTPGET_H

#include <QMainWindow>
#include <QString>
#include <QNetworkRequest>

namespace Ui {
class HttpGet;
}

class HttpGet : public QMainWindow
{
    Q_OBJECT

protected:
   QString url;
    QString path;
   QString proxy_ip="";
    int proxy_port=0;
public:
    explicit HttpGet(QWidget *parent = nullptr);
    void getPath(QString cale){this->path=cale;};
   // ~HttpGet();

private slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

    void on_ip_proxy_editingFinished();

    void on_port_proxy_editingFinished();

private:
    Ui::HttpGet *ui;
   // void savepacket(QString url, QString data);
    void saveRequest(QNetworkRequest request, QString url_addr);
    void saveReply(const QString& packetType, const QString& sourceIP, const QString& destinationIP, int messageLength);
};

#endif // HTTPGET_H
