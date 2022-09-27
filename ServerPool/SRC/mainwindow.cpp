#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Data += QString("Start")+QString("\r\n");
    ui->ViewCond->setText(Data);

    TcpS.reset(new TcpServer(QHostAddress::Any, nPort,this));
    connect(TcpS.data(), SIGNAL(Connected(qintptr,ThreadRuning**)),
            this,        SLOT(Connected(qintptr,ThreadRuning**)));
    connect(TcpS.data(), SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this,        SLOT(Error(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Begin(int descriptor,QTcpSocket *Socket)
{
    Data += QString("begin        -    ")+QString().setNum(descriptor)+
            QString("   ")+QString().setNum(int(Socket))+QString("\r\n");
    ui->ViewCond->setText(Data);
}

void MainWindow::End(int descriptor,QTcpSocket *Socket)
{
    Data += QString("End          -    ")+QString().setNum(descriptor)+
            QString("   ")+QString().setNum(int(Socket))+QString("\r\n");
    ui->ViewCond->setText(Data);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    ui->ViewCond->resize(size().width()-2*ui->ViewCond->x(),
                         size().height()-ui->ViewCond->y()-ui->ViewCond->x());
}

void MainWindow::Connected(qintptr handle,ThreadRuning **Socket)
{
    *Socket = new LitStat(handle);
    if (static_cast<LitStat*>((*Socket))->isDB_Error() == false)
    {
        connect(*Socket, SIGNAL(Begin(int,QTcpSocket*)),
                this,    SLOT(Begin(int,QTcpSocket*)));
        connect(*Socket, SIGNAL(End(int,QTcpSocket*)),
                this,    SLOT(End(int,QTcpSocket*)));
        Data += QString("Connected    -    0x")+QString().setNum(int(*Socket),16)+QString("\r\n");
    }
    else
        Data += QString("No Connected -    ")+static_cast<LitStat*>((*Socket))->GetDB_Error()+QString("\r\n");
    ui->ViewCond->setText(Data);
}

void MainWindow::DisConnected(QTcpSocket *Socket)
{
    Data += QString("DisConnected -    0x")+QString().setNum(int(Socket),16)+QString("\r\n");
    ui->ViewCond->setText(Data);
}

void MainWindow::Error(QAbstractSocket::SocketError Err)
{
    Data += QString("Error        -    ")+QString().setNum(Err)+
            QString("  ")+TcpS.data()->errorString()+QString("\r\n");
    ui->ViewCond->setText(Data);
}
