#include "mwnd.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mwnd wnd;
    wnd.show();
    return a.exec();
}
