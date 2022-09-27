#include <QDebug>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Method->addItem(QString(Method_Word));
    ui->Method->addItem(QString(Method_Char));

    C_tcp = new ClientTCP(this);
    connect(C_tcp, SIGNAL(objectState(int)), SLOT(objectState(int)));
    connect(C_tcp, SIGNAL(sendError()), SLOT(sendError()));
    connect(C_tcp, SIGNAL(receivedText()), SLOT(receivedText()));
}

MainWindow::~MainWindow()
{
    delete C_tcp;
    delete ui;
}

void MainWindow::objectState(int St)
{
    switch (St)
    {
    case ObjectState_Connect:
        ui->ViewCondition->setText("Connect");
        break;
    case ObjectState_Close:
        ui->ViewCondition->setText("Close");
        break;
    }
    ui->Send->setEnabled(C_tcp->getState());
}

void MainWindow::receivedText()
{
    ui->ViewRes->setText(C_tcp->getText());
}

void MainWindow::sendError()
{
    ui->ViewCondition->setText(C_tcp->getTextError());
}

void MainWindow::on_Open_clicked()
{
//    FileName = QFileDialog::getOpenFileName(this,"Open File","",
//                                                   "Text files (*.txt)");
    FileName = QString("D:/Work/TestWork/ClientServer/T_.txt");
    if (FileName.isEmpty() == false)
    {
        QString S = Serv.open(FileName);
        if (S.isEmpty() == false)
        {
            ui->ViewText->setText(S);
            ui->ViewRes->clear();
        }
    }
}

void MainWindow::on_Send_clicked()
{
    C_tcp->sendToServerTCP(ui->Method->currentText(),FileName,ui->ViewText->toPlainText().toUtf8());
}

void MainWindow::on_Connet_clicked()
{
    C_tcp->connectTCP(ui->IP->text());
}

void MainWindow::on_Clear_clicked()
{
    ui->ViewRes->clear();
}

