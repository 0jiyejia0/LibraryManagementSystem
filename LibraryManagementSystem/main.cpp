#include "LibraryManagementSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LibraryManagementSystem w;
    w.show();
    return a.exec();
}
