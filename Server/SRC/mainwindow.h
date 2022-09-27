#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include "db_litestat.h"

#include "../../Common/Common.h"
#include "../../CommonServer/wordstatistics.h"
#include "../../CommonServer/charstatistics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public WordStatistics, public CharStatistics
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTcpServer *TcpServer;
    QTcpSocket *ClientSocket;
    bool isClose;
    QByteArray BuffOut;
    QString Method;
    QString ID_FileName;

    DB_LiteStat *DataLite;

protected:
    void sendToClient(void);
    QString PrepText(QString);

    void Send(QString,int) override;

private slots:
    void deleteLater     (                            );
    void slotConnected   (                            );
    void destroyed       (QObject*                    );
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
};
#endif // MAINWINDOW_H
