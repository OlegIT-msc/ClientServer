#ifndef OPENFILE_H
#define OPENFILE_H

#include <QObject>
#include <QString>

class OpenFile : public QObject
{
    Q_OBJECT
public:
    explicit OpenFile(QObject *parent = nullptr);
    virtual ~OpenFile();

public:
    Q_INVOKABLE QString open(QString);
    Q_INVOKABLE QString delete_WFile(QString);

signals:

};

#endif // OPENFILE_H
