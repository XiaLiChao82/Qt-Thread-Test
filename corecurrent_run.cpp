#include "corecurrent_run.h"

corecurrent_run::corecurrent_run(QObject *parent) : QObject(parent)
{
    connect(this, &corecurrent_run::sig1, [this]()
    {
        QtConcurrent::run(this, &corecurrent_run::onSig1);
    });

    connect(this, &corecurrent_run::sig2, [this]()
    {
        QtConcurrent::run(this, &corecurrent_run::onSig2);
    });

    connect(this, &corecurrent_run::sig1, [this]()
    {
        QtConcurrent::run([this]()
        {
            qDebug() << "sig1 lambda thread id:" << QThread::currentThreadId();
        });
    });
}

void corecurrent_run::start()
{
    qDebug() << "QtConcurrent::run parent thread id:" << QThread::currentThreadId();
//    QtConcurrent::run(this, &corecurrent_run::onSig1);
//    QtConcurrent::run(this, &corecurrent_run::onSig2);
    emit sig1();
    emit sig2();
}

void corecurrent_run::onSig1()
{
    qDebug() << "sig1 thread id:" << QThread::currentThreadId();
}

void corecurrent_run::onSig2()
{
    qDebug() << "sig2 thread id:" << QThread::currentThreadId();
}
