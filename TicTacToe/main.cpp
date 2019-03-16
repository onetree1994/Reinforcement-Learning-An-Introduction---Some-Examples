#include "gridworld.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GridWorld w;
    w.show();

    return a.exec();
}
