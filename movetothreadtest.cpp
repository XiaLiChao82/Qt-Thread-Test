#include "movetothreadtest.h"

moveToThreadTest::moveToThreadTest(QObject *parent) : QObject(parent)
{
    m_thread.start();
    this->moveToThread(&m_thread);
    qDebug() << "moveToThread parent thread id:" << QThread::currentThreadId();
}

void moveToThreadTest::onSig()
{
    printThreadID();
}

void moveToThreadTest::printThreadID()
{
    qDebug() << "moveToThread child thread id:" << QThread::currentThreadId();
}
