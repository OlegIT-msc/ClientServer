#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include "../../Common/Common.h"

enum {
    ObjectState_Connect,
    ObjectState_Close
};

class ClientTCP : public QObject
{
    Q_OBJECT

public:
    explicit ClientTCP(QObject *parent = nullptr);
    virtual ~ClientTCP();

private:
    QTcpSocket *TcpSocket;
    bool isConnectTCP;
    QString Text;
    QString strError;

public:
    void connection_InitTCP(void);
    void disConnectTCP(void);
    Q_INVOKABLE QString getText(void) {return Text;}
    Q_INVOKABLE QString getTextError(void) {return strError;}
    Q_INVOKABLE bool getState(void) {return isConnectTCP;}
    Q_INVOKABLE int connectTCP(QString);
    Q_INVOKABLE void sendToServerTCP(QString, QString, QString);

public slots:
    void slotReadyRead      (                            );
    void slotError          (QAbstractSocket::SocketError);
    void slotConnectedTCP   (                            );
    void slotDisConnectedTCP(                            );

signals:
    void objectState(int);
    void sendError();
    void receivedText();
};

#endif // CLIENTTCP_H
