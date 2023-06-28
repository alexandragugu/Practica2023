#ifndef DNSWINDOW_H
#define DNSWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QString>

namespace Ui {
class DNSWindow;
}

class DNSWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DNSWindow(QWidget *parent = nullptr);
    void getPath(QString cale){ this->path=cale; };
    ~DNSWindow();
protected:
    QString path;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::DNSWindow *ui;
    QTreeWidget *treeWidget;
};

#endif // DNSWINDOW_H
