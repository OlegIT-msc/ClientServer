#include "threadruning.h"

ThreadRuning::ThreadRuning(qintptr handle,QObject *parent) : QObject(parent)
{
    descriptor = handle;
}

void ThreadRuning::run()
{
    QTcpSocket *Socket = new QTcpSocket();
    Socket->setSocketDescriptor(descriptor);

    emit Begin(int(descriptor),Socket);

    Socket->waitForReadyRead();
    Data = Socket->readAll();

    Data = DataProcessing(Data);

    Socket->write(Data);
    Socket->waitForBytesWritten();

    Socket->disconnectFromHost();
    Socket->close();

    emit End(int(descriptor),Socket);

    Socket->deleteLater();
}
