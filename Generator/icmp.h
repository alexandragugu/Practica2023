#ifndef ICMP_H
#define ICMP_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class ICMP;
}

class ICMP : public QMainWindow
{
    Q_OBJECT
protected:
    QString ip;
    QString id;
    QString secNr;
public:
    explicit ICMP(QWidget *parent = nullptr);
    ~ICMP();

private slots:
    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::ICMP *ui;
};

#endif // ICMP_H
