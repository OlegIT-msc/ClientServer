#include "db_litestat.h"

DB_LiteStat::DB_LiteStat(QString)
{
    Err = false;
    DB_Tab = nullptr;
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("./StatDB.db");
    if (DB.open() == false)
        StrError = DB.lastError().text();
    else
    {
        if (DB.isValid() == false)
        {
            StrError = DB.lastError().text();
            Err = DB.lastError().isValid();
        }
        else
        {
            DB_Tab = new QSqlQuery(DB);
            QStringList ListTables = DB.tables(QSql::Tables);
            if (ListTables.contains(QString("FileName")) == false)
                DB_Tab->exec(QString("CREATE TABLE FileName ("
                                     "ID INTEGER NOT NULL PRIMARY KEY,"
                                     "Name TEXT NOT NULL,"
                                     "Method TEXT NOT NULL,"
                                     "Data DATE DEFAULT CURRENT_DATE,"
                                     "Time TIME DEFAULT CURRENT_TIME)"));
            if (ListTables.contains(QString("Stat")) == false)
                DB_Tab->exec(QString("CREATE TABLE Stat ("
                                     "ID INTEGER NOT NULL PRIMARY KEY,"
                                     "ID_FileName INTEGER,"
                                     "Word TEXT NOT NULL,"
                                     "Count INTEGER NOT NULL,"
                                     "FOREIGN KEY (ID_FileName) REFERENCES FileName(ID))"));
            StrError = DB_Tab->lastError().text();

            DB_Tab->last();
        }
    }
}

DB_LiteStat::~DB_LiteStat()
{
    DB.close();
}

QString DB_LiteStat::GetLast_ID(void)
{
    QString SSQL = QString("SELECT max(ID) FROM FileName");
    DB_Tab->exec(SSQL);
    DB_Tab->first();
    return DB_Tab->value(0).toString();
}

bool DB_LiteStat::InsertDataFileName(QString S1,QString S2,QString)
{
    QString SSQL = QString("INSERT INTO FileName (Name,Method) VALUES ('")+S1+
            QString("', '")+S2+QString("')");
    DB_Tab->exec(SSQL);
    DB_Tab->first();
    return true;
}

bool DB_LiteStat::InsertDataStat(QString S1,QString S2,QString S3)
{
    QString SSQL = QString("INSERT INTO Stat (ID_FileName,Word,Count) VALUES ('")+
            S1+QString("', '")+S2+QString("', '")+S3+QString("')");
    DB_Tab->exec(SSQL);
    DB_Tab->first();
    return true;
}

