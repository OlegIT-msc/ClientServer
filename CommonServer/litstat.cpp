#include <QTime>
#include <QCoreApplication>
#include "litstat.h"

DB_LiteStat *LitStat::DataLite = nullptr;
QMutex LitStat::Mt;

LitStat::LitStat(qintptr handle, QObject *parent) : ThreadRuning(handle,parent)
{
    Method = QString();
    ID_FileName =  QString();
    DB_Error = false;
    if (DataLite == nullptr)
    {
        DataLite = new DB_LiteStat("./StatDB.db");
        DB_Error = !DataLite->GetStrError().isEmpty();
    }
}

void LitStat::Send(QString S,int V)
{
    Mt.lock();
    DataLite->InsertDataStat(ID_FileName,S,QString().setNum(V));
    Mt.unlock();
}

QString LitStat::PrepText(QString S)
{
    QString FileName;
    int Index;
    S.remove(0,1);
    Index = S.indexOf(Sp_);
    FileName = S;
    FileName.remove(Index,FileName.length());
    Mt.lock();
    DataLite->InsertDataFileName(FileName,Method,QString());
    ID_FileName = DataLite->GetLast_ID();
    Mt.unlock();
    S.remove(0,Index+QString(Sp_).length());
    return S;
}

QByteArray LitStat::DataProcessing(QByteArray D)
{
    if (D[0] == Method_Word[0])
    {
        Method = Method_Word;
        D = WordLength(PrepText(QString(D)),QString("\r\n")).toUtf8();
    }
    if (Data[0] == Method_Char[0])
    {
        Method = Method_Char;
        D = CharCount(PrepText(QString(D)),QString("\r\n")).toUtf8();
    }

//    while(Data.isEmpty() == true) {}
//    QTime dieTime= QTime::currentTime().addSecs(3);
//    while (QTime::currentTime() < dieTime)
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    return D;
}
