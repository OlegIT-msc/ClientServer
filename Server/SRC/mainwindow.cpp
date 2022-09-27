#include <QDebug>
#include <QDataStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ID_FileName = QString();
    isClose = false;
    TcpServer = new QTcpServer(this);
    if (!TcpServer->listen(QHostAddress::Any, nPort)) {
        TcpServer->close();
        return;
    }
    connect(TcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotConnected()));

    DataLite = new DB_LiteStat("./StatDB.db");
    ui->ErrorDB->setText(DataLite->GetStrError());
    qDebug() << DataLite->GetStrError();
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::Send(QString S,int V)
{
    DataLite->InsertDataStat(ID_FileName,S,QString().setNum(V));
}

void MainWindow::slotConnected()
{
    ClientSocket = TcpServer->nextPendingConnection();
    if (ClientSocket != nullptr)
    {
//        connect(pClientSocket, SIGNAL(disconnected()),
//                pClientSocket, SLOT(deleteLater()));
        connect(ClientSocket, SIGNAL(disconnected()),
                this, SLOT(deleteLater()));
        connect(ClientSocket, SIGNAL(readyRead()),
                this,          SLOT(slotReadyRead()));
        connect(ClientSocket, SIGNAL(destroyed(QObject*)),
                this,          SLOT(destroyed(QObject*)));
        isClose = false;
        ui->ViewCondition->setText(QString("Соединение установлено"));
    }
}

void MainWindow::deleteLater()
{
    isClose = true;
    ClientSocket->deleteLater();
    ui->ViewCondition->setText(QString("Соединение разовано"));
    ui->ViewRes->clear();
}

void MainWindow::destroyed(QObject*)
{
    ClientSocket = nullptr;
}

void MainWindow::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(ClientSocket->errorString())
                    );
    ui->ViewCondition->setText(strError);
    ui->ViewRes->clear();
}

QString MainWindow::PrepText(QString S)
{
    QString FileName;
    int Index;
    S.remove(0,1);
    Index = S.indexOf(Sp_);
    FileName = S;
    FileName.remove(Index,FileName.length());
    DataLite->InsertDataFileName(FileName,Method,QString());
    ID_FileName = DataLite->GetLast_ID();
    S.remove(0,Index+QString(Sp_).length());
    return S;
}

typedef QTcpSocket* TCP_S_ptr;
void MainWindow::slotReadyRead()
{
    QString Text;
    QTcpSocket *ClientSocket = TCP_S_ptr(sender());
    if (ClientSocket != nullptr)
    {
        Text = QString(ClientSocket->readAll());

        if (Text[0] == Method_Word[0])
        {
            Method = Method_Word;

            Text = PrepText(Text);
            BuffOut = WordLength(Text,QString("\r\n")).toUtf8();
        }
        if (Text[0] == Method_Char[0])
        {
            Method = Method_Char;
            Text = PrepText(Text);
            BuffOut = CharCount(Text,QString("\r\n")).toUtf8();
        }
        ui->ViewRes->setText(Text);
        sendToClient();
    }
}

void MainWindow::sendToClient(void)
{
    if (isClose == false && ClientSocket != nullptr && ClientSocket->isOpen() == true &&
            BuffOut.isEmpty() == false)
    {
        ClientSocket->write(BuffOut);
        ClientSocket->waitForBytesWritten();
    }
}
