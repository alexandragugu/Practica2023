#ifndef DNSOPTIUNI_H
#define DNSOPTIUNI_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class DNSOptiuni;
}

class DNSOptiuni : public QMainWindow
{
protected:
    Q_OBJECT
    QString packet_type;
    QString tip;
    QString ip;
    QString domeniu;
    QString port;
    QString info;
    QString clasa;

public:
    DNSOptiuni(QWidget *parent = nullptr);
    //DNSOptiuni(QString type);
    void getType(QString tip){this->packet_type=tip;};
    ~DNSOptiuni();


private slots:

    void on_OK_clicked();

   // void on_lineEdit_editingFinished();

    void on_lineEdit_4_editingFinished();

  //  void on_lineEdit_4_editingFinished();

   // void on_lineEdit_2_editingFinished();

  //  void on_lineEdit_5_editingFinished();


    //void on_lineEdit_4_editingFinished();

private:
    Ui::DNSOptiuni *ui;
};

#endif // DNSOPTIUNI_H
