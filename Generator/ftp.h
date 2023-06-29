#ifndef FTP_H
#define FTP_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class FTP;
}

class FTP : public QMainWindow
{
    Q_OBJECT
protected:
    QString adresaServer="";
    int port_number;
    QString user;
    QString parola;
    QString cale_sursa;
    QString cale_destinatie;
    QString path;
public:
    explicit FTP(QWidget *parent = nullptr);
    void getPath(QString cale){this->path=cale;};
  //  ~FTP();

private slots:
    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_pushButton_clicked();

    void on_lineEdit_6_editingFinished();

    QString generateRamdomIp();

private:
    Ui::FTP *ui;
};

#endif // FTP_H
