#include "tcpserver.h"

TcpServer::TcpServer(QHostAddress Adr,int nPort,QObject *parent) : QTcpServer(parent)
{
    isTrue = true;
    if (!listen(Adr, nPort))
    {
        close();
        isTrue = false;
    }
}

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
    isTrue = false;
}

TcpServer::~TcpServer()
{
    ThreadPool.clear();
}

bool TcpServer::Start(QHostAddress Adr,int nPort)
{
    if (!listen(Adr, nPort))
    {
        close();
        return false;
    }
    isTrue = true;
    return true;
}

void TcpServer::incomingConnection(qintptr handle)
{
    emit Connected(handle,&ClientSocket);
    ThreadPool.start(ClientSocket);
}
