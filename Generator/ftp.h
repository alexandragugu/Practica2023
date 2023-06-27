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
    QString adresaServer;
    QString user;
    QString parola;
    QString cale_sursa;
    QString cale_destinatie;
public:
    explicit FTP(QWidget *parent = nullptr);
    ~FTP();

private slots:
    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::FTP *ui;
};

#endif // FTP_H
