#ifndef ICMPWINDOW_H
#define ICMPWINDOW_H

#include <QMainWindow>

namespace Ui {
class ICMPWindow;
}

class ICMPWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ICMPWindow(QWidget *parent = nullptr);
    ~ICMPWindow();

private:
    Ui::ICMPWindow *ui;
};

#endif // ICMPWINDOW_H
