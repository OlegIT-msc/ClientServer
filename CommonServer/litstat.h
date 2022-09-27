#ifndef LITSTAT_H
#define LITSTAT_H

#include <QMutex>
#include "threadruning.h"
#include "../../Common/Common.h"
#include "../../CommonServer/wordstatistics.h"
#include "../../CommonServer/charstatistics.h"
#include "../../CommonServer/db_litestat.h"

class LitStat : public ThreadRuning, public WordStatistics, public CharStatistics
{
public:
    explicit LitStat(qintptr,QObject *parent = nullptr);

public:
    QByteArray DataProcessing(QByteArray) override;
    void Send(QString,int) override;

    bool isDB_Error(void) {return DB_Error;}
    QString GetDB_Error(void) {return DataLite->GetStrError();}

protected:
    QString PrepText(QString);

protected:
    static DB_LiteStat *DataLite;
    static QMutex Mt;
    bool DB_Error;
    QString Method;
    QString ID_FileName;

signals:

};

#endif // LITSTAT_H
