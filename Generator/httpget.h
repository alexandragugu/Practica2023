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
public:
    explicit HttpGet(QWidget *parent = nullptr);
    ~HttpGet();

private slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::HttpGet *ui;
   // void savepacket(QString url, QString data);
    void saveRequest(QNetworkRequest request, QString url_addr);
    void saveReply(const QString& packetType, const QString& sourceIP, const QString& destinationIP, int messageLength);
};

#endif // HTTPGET_H
