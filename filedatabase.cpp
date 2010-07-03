#include "filedatabase.h"
#include <QDir>
#include <QVector>
#include <QFile>

#include <QDebug>
#include <QVariant>

FileDatabase::FileDatabase(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE","file.db");
    db.setDatabaseName(QDir::homePath()+"/.rationality/file.db");

    if(!db.open())
           qWarning()<<"Errore di connessione";
    myQuery = QSqlQuery(db);

    if (myQuery.exec("CREATE TABLE tag (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL);")) qWarning()<<"Tabella creata";
    if (myQuery.exec("CREATE TABLE parent (child INTEGER NOT NULL, parent INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
    if (myQuery.exec("CREATE TABLE filetag(file INTEGER NOT NULL, tag INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
    if (myQuery.exec("CREATE TABLE file (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL,  path TEXT NOT NULL);")) qWarning()<<"Tabella creata";

    location="Root";

}

void FileDatabase::appendFilter(QString f){
    filters.push_back(f);
}

void FileDatabase::setLocation(QString tag){
    location=tag;
}

QList<Element*> FileDatabase::Elements(){
    QString temp;

        QList<Element*> list;
        QString index;
        myQuery.exec("SELECT tag.key  FROM tag WHERE tag.name = '"+location+"' ;");
     while (myQuery.next()) {
            index = myQuery.value(0).toString();
            
        }
        QSqlQuery query = QSqlQuery(db);
        int tid;
        QString child;
        myQuery.exec("SELECT tag.name,tag.key FROM parent JOIN tag ON parent.child=tag.key WHERE parent.parent="+index+";");
        //int j=0;
        while (myQuery.next()){
            Element * e = new Element();
            temp=myQuery.value(0).toString();
            tid=myQuery.value(1).toInt();
            if (!query.exec("SELECT tag.name FROM tag JOIN parent ON parent.child=tag.key WHERE parent.parent ="+QString::number(tid,'0',0)+";")) qWarning()<<"Errore";
            while (query.next()){
                child=query.value(0).toString();
                if (QString::compare(child,location)!=0 && !e->Tags().contains(child) && QString::compare(temp,child))
                    e->addTag(child);
            }
            e->setRelation(true);
            e->setName(temp);

            list.push_back(e);
        }
        myQuery.exec("SELECT file.name,file.path,file.key FROM filetag JOIN file ON filetag.file=file.key WHERE filetag.tag="+index+";");
        int fid;
        QFile * fileInfo;
        QString tag;
        while (myQuery.next()){
            ElementFile * e = new ElementFile();
            temp=myQuery.value(0).toString();
            fid=myQuery.value(2).toInt();


            query.exec("SELECT tag.name FROM filetag JOIN tag ON filetag.tag=tag.key WHERE filetag.file="+QString::number(fid)+";");
            while (query.next()){
                tag=query.value(0).toString();
                if (QString::compare(tag,location)!=0 && !e->Tags().contains(tag))
                    e->addTag(tag);
            }
            e->setRelation(false);
            e->setName(temp);
            e->setPath(myQuery.value(1).toString());
            fileInfo = new QFile(e->Path()+e->Name());
            if (mime.fromFile(fileInfo).length()){
                e->setType(mime.fromFile(fileInfo));
                e->setDescription(mime.description());
            }
            else {
                e->setType("Unknow");
                e->setDescription("Unknow");
            }
            delete fileInfo;
            if (!list.contains(e))
                list.push_back(e);
        }

        return list;

}

QList<Element*> FileDatabase::filtredElements(){
    QList <Element*> filtred;
    QList <int> tags;
    if (filters.length()==0) return filtred;


    for (int i=0;i< filters.length(); i++){
       // if (filters[i].type==INTERSECT){
           myQuery.exec("SELECT tag.key FROM tag WHERE tag.name='"+filters[i]+"';");
           if (myQuery.next())
               tags.push_back(myQuery.value(0).toInt());
       // }
    }
    int id;
    QFile * fileInfo;
    QList <int> file;
    QList <int> files;
    QSqlQuery query(db);
    for (int i=0; i<tags.length();i++){
        myQuery.exec("SELECT filetag.file FROM filetag WHERE filetag.tag="+QString::number(tags[0])+";");
        while (myQuery.next()){
            id=myQuery.value(0).toInt();

            file.clear();
            query.exec("SELECT filetag.tag FROM filetag WHERE filetag.file="+QString::number(id)+";");
            while (query.next())
                file.push_back(query.value(0).toInt());
            bool a=true;
            for (int j=0; j<tags.length(); j++){
                if (!file.contains(tags[j])) a = false;
            }
            if (a && !files.contains(id)) files.push_back(id);
        }
    }
    ElementFile * e;
    QString path;
    QString t;
    for (int i=0; i<files.length();i++){
        e=new ElementFile();
        myQuery.exec("SELECT file.name,file.path FROM file WHERE file.key="+QString::number(files[i])+";");
        if (myQuery.next()) {
            e->setName(myQuery.value(0).toString());
            e->setPath(myQuery.value(1).toString());
        }
        query.exec("SELECT tag.name FROM filetag JOIN tag ON filetag.tag=tag.key WHERE filetag.file="+QString::number(files[i])+";");
        while (query.next()){
            t=query.value(0).toString();
            if (e->Tags().contains(t))
                e->addTag(t);
        }
        e->setRelation(false);
        path=e->Path()+e->Name();
        fileInfo = new QFile(path);
        if (mime.fromFile(fileInfo)!=""){
            e->setType(mime.fromFile(fileInfo));
            e->setDescription(mime.description());
        }
        else {
            e->setType("Unknow");
            e->setDescription("Unknow");
        }
        delete fileInfo;
        filtred.push_back(e);
    }
    return  filtred;
    
}

void FileDatabase::clearFilters(){
    filters.clear();
}
