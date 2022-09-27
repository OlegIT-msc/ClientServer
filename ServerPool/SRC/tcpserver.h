#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpSocket>
#include <QThreadPool>
#include <QtNetwork/QTcpServer>
#include <QScopedPointer>
#include "threadruning.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QHostAddress,int,QObject *parent = nullptr);
    TcpServer(QObject *parent = nullptr);
    virtual ~TcpServer();

public:
    bool Start(QHostAddress,int);

protected:
    void incomingConnection(qintptr) override;

private:
    bool isTrue;
    QThreadPool ThreadPool;
    ThreadRuning *ClientSocket;

signals:
    void Connected(qintptr,ThreadRuning**);

private slots:
};

#endif // TCPSERVER_H
