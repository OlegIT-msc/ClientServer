#ifndef CALCNUMOFELEM_H
#define CALCNUMOFELEM_H

#include <QStringList>
#include <QMap>

typedef QMap<QString,int> StringStat;

class CalcNumOfElem
{
public:
    CalcNumOfElem();

public:
    StringStat CalcElem(QStringList);
    QString MakeStat(QStringList, QString);

    virtual void Send(QString,int) = 0;
};

#endif // CALCNUMOFELEM_H
