#ifndef HTTP_H
#define HTTP_H

#include <QMainWindow>

namespace Ui {
class HTTP;
}

class HTTP : public QMainWindow
{
    Q_OBJECT

public:
    explicit HTTP(QWidget *parent = nullptr);
    ~HTTP();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::HTTP *ui;
};

#endif // HTTP_H
