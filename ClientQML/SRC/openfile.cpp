#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QByteArray>

#include "openfile.h"

OpenFile::OpenFile(QObject *parent) : QObject(parent)
{
}

OpenFile::~OpenFile()
{
}

QString OpenFile::delete_WFile(QString S)
{
    return S.remove(QString("file:///"));
}

QString OpenFile::open(QString Name)
{
    QString Text;
    QByteArray Ba;

    Name = delete_WFile(Name);
    QFile F(Name);
    Text.clear();

    QTextStream stream (&F);
    if(F.open(QIODevice::ReadOnly))
    {
        QTextStream stream (&F);
        stream.setCodec(QTextCodec::codecForName("Windows-1251"));
        Text = stream.readAll();
        F.close();
    }
//*/

    return Text;
}
