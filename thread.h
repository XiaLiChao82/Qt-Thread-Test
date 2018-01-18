#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = nullptr);

protected:
    void run();

signals:
    void sig();
public slots:
    void onSig();
    void onPrintCurrentThreadID();

private:
    bool m_isPrint;
};

#endif // THREAD_H
