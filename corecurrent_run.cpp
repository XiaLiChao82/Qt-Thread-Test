#include "corecurrent_run.h"

corecurrent_run::corecurrent_run(QObject *parent) : QObject(parent)
{
    m_count = 0;
    m_sum = 0;
    m_threadPool = new QThreadPool(this);
    m_threadPool->setMaxThreadCount(100);
    connect(this, &corecurrent_run::sig1, [this]()
    {
        QtConcurrent::run(this, &corecurrent_run::onSig1);
    });

    connect(this, &corecurrent_run::sig2, [this]()
    {
//        QtConcurrent::run(this, &corecurrent_run::onSig2);
        QtConcurrent::run([this]()
        {
            QEventLoop loop;
            QTimer timer;
            connect(&timer, &QTimer::timeout, [this]()
            {
                emit testLoop();
            });
            connect(this, &corecurrent_run::testLoop, [this]()
            {
                m_count = m_count+3;
                m_count = m_count*2;
                qDebug() << "count:" << m_count;
                qDebug() << "运行loop, thread id:" << QThread::currentThreadId();
            });

            timer.start(2000);
            qDebug() << "sig2 thread id:" << QThread::currentThreadId();
            loop.exec();
        });
    });

    connect(this, &corecurrent_run::sig1, [this]()
    {
        QtConcurrent::run([this]()
        {
            qDebug() << "sig1 lambda thread id:" << QThread::currentThreadId();
        });
    });

    m_timer = new QTimer(this);
    m_timer->setInterval(2000);

    connect(m_timer, &QTimer::timeout, [this]()
    {
        emit testLoop();
    });

    m_timer->start();
}

void corecurrent_run::start()
{
    qDebug() << "QtConcurrent::run parent thread id:" << QThread::currentThreadId();
//    QtConcurrent::run(this, &corecurrent_run::onSig1);
//    QtConcurrent::run(this, &corecurrent_run::onSig2);
    emit sig1();
    emit sig2();

//    QtConcurrent::run(onSig3, 3);
    for(int i = 0; i < 100; i++)
    {
        int num = i;
        QtConcurrent::run(m_threadPool, this, &corecurrent_run::onSig3, num);
    }
}

void corecurrent_run::onSig1()
{
    qDebug() << "sig1 thread id:" << QThread::currentThreadId();
}

void corecurrent_run::onSig2()
{
    QEventLoop loop;
    QTimer timer;
    connect(&timer, &QTimer::timeout, [this]()
    {
        emit testLoop();
    });
    connect(this, &corecurrent_run::testLoop, [this]()
    {

        qDebug() << "运行loop, thread id:" << QThread::currentThreadId();
    });

    timer.start(2000);
    qDebug() << "sig2 thread id:" << QThread::currentThreadId();
    loop.exec();
}

void corecurrent_run::onSig3(int n)
{
    qDebug() << "sig3 thread id:" << QThread::currentThreadId() << ", args:" << n;
    m_sum++;
    qDebug() << "m_sum = " << m_sum;
}
