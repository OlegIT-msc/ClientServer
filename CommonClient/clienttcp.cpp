#include <QFileInfo>
#include "clienttcp.h"

ClientTCP::ClientTCP(QObject *parent) : QObject(parent)
{
    isConnectTCP = false;
    connection_InitTCP();
}

ClientTCP::~ClientTCP()
{
}

void ClientTCP::connection_InitTCP(void)
{
    TcpSocket = new QTcpSocket(this);

    connect(TcpSocket, SIGNAL(connected()), SLOT(slotConnectedTCP()));
    connect(TcpSocket, SIGNAL(disconnected()), SLOT(slotDisConnectedTCP()));
    connect(TcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(TcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );
}

int ClientTCP::connectTCP(QString S)
{
    TcpSocket->connectToHost(S, nPort);
    return 0;
}

void ClientTCP::disConnectTCP(void)
{
    if (TcpSocket->isOpen() == false)
        return;
    TcpSocket->disconnectFromHost();
    TcpSocket->close();
}

void ClientTCP::slotConnectedTCP()
{
    isConnectTCP = true;
    emit objectState(ObjectState_Connect);
}

void ClientTCP::slotDisConnectedTCP()
{
    isConnectTCP = false;
    emit objectState(ObjectState_Close);
}

void ClientTCP::slotReadyRead()
{
    if (isConnectTCP == false)
        return;

    Text = QString(TcpSocket->readAll());
    emit receivedText();
}

void ClientTCP::slotError(QAbstractSocket::SocketError err)
{
    strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(TcpSocket->errorString())
                    );
    emit sendError();
    TcpSocket->close();
}

void ClientTCP::sendToServerTCP(QString Metod,QString FileName,QString S)
{
    if (isConnectTCP == false)
        return;
    S.insert(0,QString(Sp_));
    S.insert(0,QFileInfo(FileName).baseName());
    if (Metod == Method_Word)
        S.insert(0,QString(Method_Word[0]));
    if (Metod == Method_Char)
        S.insert(0,QString(Method_Char[0]));
    TcpSocket->write(S.toUtf8());
    TcpSocket->waitForBytesWritten();
}
