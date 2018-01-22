#include "thread.h"

Thread::Thread(QObject *parent) : QThread(parent)
{
    connect(this, &Thread::sig, this, &Thread::onSig);
    m_isPrint = false;
    m_list.clear();
    qDebug() << "QThread parent Thread ID:" << QThread::currentThreadId();
}

void Thread::onSig()
{
    onPrintCurrentThreadID();
}

void Thread::onPrintCurrentThreadID()
{
    qDebug() << "current Thread ID:" << QThread::currentThreadId();
    if(!m_list.isEmpty())
    {
        qDebug() << "get list first value:" << m_list.takeFirst();
    }
}

void Thread::run()
{
    qDebug() << "child Thread ID:" << QThread::currentThreadId();
    while(1)
    {
        if(!m_isPrint)
        {
//            onSig();
            m_list.append(QString("test"));
//            connect(this, &Thread::sig, this, &Thread::onSig, Qt::DirectConnection);
            emit sig();
            m_isPrint = true;
        }
    }
}
