#include "preptext.h"
#include "../../Common/Common.h"

PrepText::PrepText()
{

}

void PrepText::operator()(QString S)
{
    QString FileName;
    int Index;
    S.remove(0,1);
    Index = S.indexOf(Sp_);
    FileName = S;
    FileName.remove(Index,FileName.length());
    DataLite->InsertDataFileName(FileName,Method,QString());
    ID_FileName = DataLite->GetLast_ID();
    S.remove(0,Index+QString(Sp_).length());
    return S;
}
