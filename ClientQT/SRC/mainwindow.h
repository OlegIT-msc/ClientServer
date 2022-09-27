#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../CommonClient/clienttcp.h"
#include "../../CommonClient/service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void objectState(int);
    void sendError();
    void receivedText();

    void on_Open_clicked();

    void on_Send_clicked();

    void on_Connet_clicked();

    void on_Clear_clicked();

private:
    Ui::MainWindow *ui;
    ClientTCP *C_tcp;
    QString FileName;
    Service Serv;
};

#endif // MAINWINDOW_H
