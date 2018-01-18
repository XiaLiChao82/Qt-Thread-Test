#ifndef MOVETOTHREADTEST_H
#define MOVETOTHREADTEST_H

#include <QObject>
#include <QThread>
#include <QDebug>

class moveToThreadTest : public QObject
{
    Q_OBJECT
public:
    explicit moveToThreadTest(QObject *parent = nullptr);

signals:
    void sig();

public slots:
    void onSig();

private:
    void printThreadID();

    QThread m_thread;
};

#endif // MOVETOTHREADTEST_H
