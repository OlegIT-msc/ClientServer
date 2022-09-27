#include "wordstatistics.h"
#include <QRegExp>

WordStatistics::WordStatistics()
{
}

QString WordStatistics::WordLength(QString Sl,QString Sep)
{
    QStringList LText;

    LText = Sl.trimmed().split(QRegExp(QString("\\W+")));

    return MakeStat(LText,Sep);
}
