
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT
protected:
    QString path="D:/Practica2023/simulare";
    int ok=0;
public:
    MainWindow(QWidget *parent = nullptr);
   // ~MainWindow();

private slots:
    void on_ICMP_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QString getNumber();
};

#endif // MAINWINDOW_H
