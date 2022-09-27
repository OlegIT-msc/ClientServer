#ifndef WORDSTATISTICS_H
#define WORDSTATISTICS_H

#include <QStringList>
#include "calcnumofelem.h"

class WordStatistics : public virtual CalcNumOfElem
{
public:
    WordStatistics();

public:
    QString WordLength(QString,QString);
};

#endif // WORDSTATISTICS_H
