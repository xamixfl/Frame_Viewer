#include <QApplication>

#include "mainwindow.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    mainwindow w;
    if (! w.init_check())
        return EXIT_FAILURE;

    w.show();
    return a.exec();
}
