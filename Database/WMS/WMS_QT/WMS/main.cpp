#include "login.h"
#include <QApplication>
#include "control.h"
Control *CONTROL = new Control();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
