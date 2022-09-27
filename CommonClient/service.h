#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QString>

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QObject *parent = nullptr);
    virtual ~Service();

protected:
    QString FileName;

protected:
    QString delete_WFile(QString);

public:
    Q_INVOKABLE QString open(QString);
    Q_INVOKABLE QString getFileName(void) {return FileName;}
    Q_INVOKABLE QString getMethod(int);

signals:

};

#endif // SERVICE_H
