#ifndef CORECURRENT_RUN_H
#define CORECURRENT_RUN_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>

class corecurrent_run : public QObject
{
    Q_OBJECT
public:
    explicit corecurrent_run(QObject *parent = nullptr);

signals:
    void sig1();
    void sig2();
    void testLoop();

public slots:
    void start();
    void onSig1();
    void onSig2();

public:
    void onSig3(int n);
    QTimer *m_timer;
    int m_count;
    int m_sum;
    QThreadPool *m_threadPool;
};

#endif // CORECURRENT_RUN_H
