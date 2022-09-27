#ifndef CHARSTATISTICS_H
#define CHARSTATISTICS_H

#include <QStringList>
#include "calcnumofelem.h"

class CharStatistics : public virtual CalcNumOfElem
{
public:
    CharStatistics();

public:
    QString CharCount(QString,QString);
};

#endif // CHARSTATISTICS_H
