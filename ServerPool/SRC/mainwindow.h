#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QStringListModel>
#include "tcpserver.h"
#include "../../CommonServer/litstat.h"
#include "../../CommonServer/db_litestat.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QString Data;

    QScopedPointer<TcpServer> TcpS;

private slots:
    void Error(QAbstractSocket::SocketError);
    void Connected(qintptr,ThreadRuning**);
    void DisConnected(QTcpSocket*);

    void Begin(int, QTcpSocket*);
    void End(int, QTcpSocket*);
};
#endif // MAINWINDOW_H
