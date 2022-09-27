#ifndef THREADRUNING_H
#define THREADRUNING_H

#include <QObject>
#include <QByteArray>
#include <QRunnable>
#include <QtNetwork/QTcpSocket>

class ThreadRuning : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit ThreadRuning(qintptr,QObject *parent = nullptr);
    virtual ~ThreadRuning(){}

public:
    void run();
    virtual QByteArray DataProcessing(QByteArray Data) {return Data;}

protected:
    qintptr descriptor;
    QByteArray Data;

signals:
    void Begin(int,QTcpSocket*);
    void End(int,QTcpSocket*);

private slots:
};

#endif // THREADRUNING_H
