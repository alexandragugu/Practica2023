#ifndef HTTP_H
#define HTTP_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class HTTP;
}

class HTTP : public QMainWindow
{
    Q_OBJECT
protected:
    QString path;
    QString ip_proxy;
    QString port_proxy;
public:
    explicit HTTP(QWidget *parent = nullptr);
    void getPath(QString cale){this->path=cale;};
  //  ~HTTP();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::HTTP *ui;
};

#endif // HTTP_H
