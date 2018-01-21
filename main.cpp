#include "mainwindow.h"
#include <QApplication>
#include "thread.h"
#include "movetothreadtest.h"
#include "corecurrent_run.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Thread thread;
    thread.start();

    moveToThreadTest _thread;
    QObject::connect(&thread, &Thread::sig, &_thread, &moveToThreadTest::onSig);

    corecurrent_run cr;
    cr.start();

    return a.exec();
}
