#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QByteArray>

#include "service.h"
#include "../../Common/Common.h"

Service::Service(QObject *parent) : QObject(parent)
{
}

Service::~Service()
{
}

QString Service::delete_WFile(QString S)
{
    return S.remove(QString("file:///"));
}

QString Service::open(QString Name)
{
    QString Text;

    FileName = delete_WFile(Name);
    QFile F(FileName);
    Text.clear();

    QTextStream stream (&F);
    if(F.open(QIODevice::ReadOnly))
    {
        stream.setCodec(QTextCodec::codecForName("Windows-1251"));
        Text = stream.readAll();
        F.close();
    }

    return Text;
}

QString Service::getMethod(int V)
{
    switch (V)
    {
    case 0:
        return QString(Method_Word);
    case 1:
        return QString(Method_Char);
    }
    return QString();
}
