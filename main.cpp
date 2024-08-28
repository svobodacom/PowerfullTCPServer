#include "dialog.h"
#include "test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Test cTest;
    cTest.doTest();

    Dialog w;
    w.show();

    return a.exec();
}
