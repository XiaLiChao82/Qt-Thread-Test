#ifndef CORECURRENT_RUN_H
#define CORECURRENT_RUN_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>

class corecurrent_run : public QObject
{
    Q_OBJECT
public:
    explicit corecurrent_run(QObject *parent = nullptr);

signals:
    void sig1();
    void sig2();

public slots:
    void start();
    void onSig1();
    void onSig2();
};

#endif // CORECURRENT_RUN_H
