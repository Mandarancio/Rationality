#include <QtCore/QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QDebug>
#include <QVariant>

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","file.db");
    db.setDatabaseName(QDir::homePath()+"/.rationality/file.db");

    if(!db.open())
           qWarning()<<"Errore di connessione";
    QSqlQuery myQuery = QSqlQuery(db);

  /*  if (myQuery.exec("CREATE TABLE tag (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL);")) qWarning()<<"Tabella creata";
//    else qWarning()<<"Errore o tabella esistente";
    if (myQuery.exec("CREATE TABLE parent (child INTEGER NOT NULL, parent INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
//    else qWarning()<<"Errore o tabella esistente";
    if (myQuery.exec("CREATE TABLE filetag(file INTEGER NOT NULL, tag INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
//    else qWarning()<<"Errore o tabella esistente";
    if (myQuery.exec("CREATE TABLE file (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL,  path TEXT NOT NULL);")) qWarning()<<"Tabella creata";
  //  else qWarning()<<"Errore o tabella esistente";
  //   myQuery.exec("INSERT INTO tag VALUES (-1,'Root');");*/
    if (myQuery.exec("CREATE TABLE tag (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,parent INTEGER NOT NULL, name TEXT NOT NULL, hidden INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
    if (myQuery.exec("CREATE TABLE filetag(file INTEGER NOT NULL, tag INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
    if (myQuery.exec("CREATE TABLE file (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL,  path TEXT NOT NULL, rating INTEGER, CONSTRAINT rating_min_5 CHECK rating < 5 );")) qWarning()<<"Tabella creata";


   if (myQuery.exec("SELECT tag.name FROM tag;")) {
        QString t;
        while (myQuery.next()){
            t=myQuery.value(0).toString();
            qWarning()<<t;
        }
    }
    if (myQuery.exec("SELECT file.name FROM file;")) {
        QString t;
        while (myQuery.next()){
            t=myQuery.value(0).toString();
            qWarning()<<t;
        }
     }





     QString cmd="";
     char c[200];
     while (1) {
         cout << "cmd: ";
         cin.getline(c,200);
         cmd = QString::fromStdString(c);
         if (QString::compare(cmd,"exit")==0) break;
         if (myQuery.exec(cmd)) cout << "\n";
         else cout << "Comando non eseguito\n";

     }
    db.close();

    return 0;
}
