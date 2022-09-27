#include <QDebug>
#include "charstatistics.h"

CharStatistics::CharStatistics()
{
}

QString CharStatistics::CharCount(QString Sl,QString Sep)
{
    QStringList LText;

    LText.clear();
    foreach (QChar El, Sl)
    {
        if (El.isLetter() == true)
            LText << El;
    }
    return MakeStat(LText,Sep);
}
