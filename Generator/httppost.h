#ifndef HTTPPOST_H
#define HTTPPOST_H

#include <QMainWindow>
#include <QString>
#include <QByteArray>

namespace Ui {
class HTTPPost;
}

class HTTPPost : public QMainWindow
{
    Q_OBJECT
protected:
    QString url;
    QString sourcefile;
    QByteArray data;
    QString from;
    QString to;
    QString path;
public:
    explicit HTTPPost(QWidget *parent = nullptr);
    void getPath(QString cale){this->path=cale;};
    ~HTTPPost();

private slots:
    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::HTTPPost *ui;
    void readData();
};

#endif // HTTPPOST_H
