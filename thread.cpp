#include "thread.h"

Thread::Thread(QObject *parent) : QThread(parent)
{
    connect(this, &Thread::sig, this, &Thread::onSig);
    m_isPrint = false;
    qDebug() << "parent Thread ID:" << QThread::currentThreadId();
}

void Thread::onSig()
{
    onPrintCurrentThreadID();
}

void Thread::onPrintCurrentThreadID()
{
    qDebug() << "current Thread ID:" << QThread::currentThreadId();
}

void Thread::run()
{
    qDebug() << "child Thread ID:" << QThread::currentThreadId();
    while(1)
    {
        if(!m_isPrint)
        {
            onSig();
            emit sig();
            m_isPrint = true;
        }
    }
}
