#include "loginui.h"
#include "testwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testwindow testwin;
    testwin.show();
    auto w = new LoginUI;
    w->show();
    return a.exec();
}
