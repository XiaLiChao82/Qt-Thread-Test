#include "mainwindow.h"
#include <QApplication>
#include <mutex>
#include <QMutex>
#include <QMutexLocker>
#include <thread>
#include <atomic>
#include <sys/time.h>
#include "thread.h"
#include "movetothreadtest.h"
#include "corecurrent_run.h"

#define MAX 10*1000*1000

long num = 0;
//std::atomic_long num{0};

std::mutex cstdmutex;

QMutex qtmutex;

void add()
{
    for(int i = 0; num < MAX; i++)
    {
//        std::unique_lock<std::mutex> locker(cstdmutex);
        QMutexLocker locker(&qtmutex);
//        cstdmutex.lock();
//        qtmutex.lock();
        num++;
//        cstdmutex.unlock();
//        qtmutex.unlock();
    }
}

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

    QThreadPool pool;
    QtConcurrent::run(&pool, &thread, &Thread::onTestThreadPool);

//    struct timeval tpstart,tpend;
//    float timeuse;
//    gettimeofday(&tpstart,NULL);

//    std::thread thread1(add);
//    std::thread thread2(add);

//    thread1.join();
//    thread2.join();

//    gettimeofday(&tpend,NULL);
//    timeuse=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000000.0;

//    qDebug()<<timeuse<<"s";

//    qDebug() << "num:" << num;

    return a.exec();
}
