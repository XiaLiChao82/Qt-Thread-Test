#include "movetothreadtest.h"

moveToThreadTest::moveToThreadTest(QObject *parent) : QObject(parent)
{
    QTimer *timer = new QTimer(this);

    timer->start(1000);

    m_thread.start();
    this->moveToThread(&m_thread);
    qDebug() << "moveToThread parent thread id:" << QThread::currentThreadId();

    connect(this, &moveToThreadTest::sig, this, &moveToThreadTest::onSig);
    connect(timer, &QTimer::timeout, this, &moveToThreadTest::sig);
//    emit sig();

}

void moveToThreadTest::onSig()
{
    printThreadID();
}

void moveToThreadTest::printThreadID()
{
    qDebug() << "moveToThread child thread id:" << QThread::currentThreadId();
}
