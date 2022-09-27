#include "calcnumofelem.h"

CalcNumOfElem::CalcNumOfElem()
{
}

StringStat CalcNumOfElem::CalcElem(QStringList S)
{
    StringStat Res;
    StringStat::iterator it;

    foreach (QString El, S)
    {
        it = Res.find(El);
        if (it != Res.end())
            ++it.value();
        else
            Res.insert(El,1);
    }
    return Res;
}

QString CalcNumOfElem::MakeStat(QStringList StrL,QString Sep)
{
    QString S;
    StringStat::iterator it;

    StringStat Res = CalcElem(StrL);

    S.clear();
    it = Res.begin();
    while (it != Res.end())
    {
        Send(it.key(),it.value());
        S += it.key()+QString("  ")+QString().setNum(it.value())+Sep;
        ++it;
    }
    return S;
}
