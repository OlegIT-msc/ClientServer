#ifndef DB_LITE_H
#define DB_LITE_H

#include <QString>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DB_LiteStat
{
public:
    DB_LiteStat(QString);
    virtual ~DB_LiteStat();

private:
    QSqlDatabase DB;
    QSqlQuery *DB_Tab;
    QString StrError;
    bool Err;

public:
    QString GetStrError(void) {return StrError;}
    bool TestError(void) {return Err;}
    QString GetLast_ID(void);
    bool InsertDataFileName(QString, QString, QString);
    bool InsertDataStat(QString, QString, QString);
};

#endif // DB_LITE_H
