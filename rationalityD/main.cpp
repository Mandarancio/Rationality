#include <QtCore/QCoreApplication>
#include <QSqlDatabase>
#include <QFile>
#include <QFileInfoList>
#include <QDir>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QDateTime>
#include <QDate>

QSqlDatabase db;

struct tag{
    QString name;
    QString parent;
    int id;
};

struct file{
    QString name;
    QString path;
};

//INSERTION  FUNCTION
bool addTag(QString name, int &tk,int parent, bool hidden=false ){
    int h=hidden;
    QSqlQuery query(db);
    if (!query.exec("INSERT INTO tag VALUES ( "+QString::number(tk)+","+QString::number(parent)+", '"+name+"'"+","+QString::number(h)+");")) return false;
    else {
        tk++;
        return true;
    }
}

bool addFile(QString name,QString path,int rating, int &fk ){
    QSqlQuery query(db);
    if (!query.exec("INSERT INTO file VALUES ( "+QString::number(fk)+",'"+name+"','"+path+"'', "+QString::number(rating)+");")) return false;
    else {
        fk++;
        return true;
    }
}

bool tagFile(int file, int tag){

    QSqlQuery query(db);
    if (!query.exec("INSERT INTO filetag VALUES ( "+QString::number(file)+","+QString::number(tag)+");")) return false;
    else {
        return true;
    }

}


//COMPARE FUNCTIONS
int containsTag(QList<tag> t1,tag t2){
    for (int i=0; i<t1.length(); i++){
        if (!QString::compare(t1[i].name,t2.name) && !QString::compare(t1[i].parent,t2.parent))
            return t1[i].id;
    }
    return 0;
}

bool containsFile(QList<file> t1,file t2){
    for (int i=0; i<t1.length(); i++){
        if (!QString::compare(t1[i].name,t2.name) && !QString::compare(t1[i].path,t2.path))
            return true;
    }
    return false;
}

//FILL DATABASE
void addDate(QList<tag> tags, QDateTime t, int key,int &tgkey){
    tag t1,t2,t3;
    int p2,p3;

    t1.name=QString::number(t.date().year());
    t2.name=QString::number(t.date().month());
    t3.name=QString::number(t.date().day());

    t1.parent="Virtual";
    t2.parent=t1.name;
    t3.parent=t2.name;

    if (!containsTag(tags,t1)){

        //ASSIGNETION OF NEW KEY AND ADDICTION TO THE TABLE TAG AND PARENT
        t1.id=tgkey;
        addTag(t1.name,tgkey,-2,true);

        p2=tgkey-1;

        t2.id=tgkey;
        addTag(t2.name,tgkey,p2,true);

        p3=tgkey-1;

        t3.id=tgkey;
        addTag(t3.name,tgkey,p3,true);
    }
    else {
        t1.id=containsTag(tags,t1);
        p2=t1.id;

        if (!containsTag(tags,t2)){

            t2.id=tgkey;
            addTag(t2.name,tgkey,p2,true);

            p3=tgkey-1;

            t3.id=tgkey;
            addTag(t3.name,tgkey,p3,true);
        }
        else {
            t2.id=containsTag(tags,t2);
            p3=t2.id;
            if (!containsTag(tags,t3)) {
                t3.id=tgkey;
                addTag(t3.name,tgkey,p3,true);
            }
            else
                t3.id=containsTag(tags,t3);
        }
    }
    //ASSIGNATION OF THE TAGS TO THE FILE
    tagFile(key,t1.id);
    tagFile(key,t2.id);
    tagFile(key,t3.id);
}

//TO UNDERSTAND IF IS BETTER MEMORIZE THE LAST UPDATE TO FILE OR THE CREATION DATE

void scanFolder(QSqlQuery & rq, int &tk, int &fk, QString path,int pId, QList<file> f, QList<tag> t){

    QDir dir(path);
    file file;
    file.path=path;
    tag tag;
    if (rq.exec("SELECT tag.name FROM tag WHERE tag.key="+QString::number(pId)+";"))
        tag.parent=rq.value(0).toString();

    QFileInfoList l=dir.entryInfoList();

    for (int i=0; i<dir.entryList().length();i++){

        if (l.at(i).isFile() && !l.at(i).isHidden()){
            file.name=dir.entryList().at(i);
            if (!containsFile(f,file)) {
                addFile(dir.entryList().at(i),path,0,fk);
                if (!tagFile(fk,pId)) qWarning()<<"Relazione non creata";
                addDate(t,l.at(i).created(),fk,tk);
            }
        }
        else if (l.at(i).isDir() && !l.at(i).isHidden() && QString::compare(dir.entryList().at(i),".") && QString::compare(dir.entryList().at(i),"..")){
            tag.name=dir.entryList().at(i);
            if (!containsTag(t,tag)) addTag(dir.entryList().at(i),tk,pId);
            scanFolder(rq,tk,fk,path+dir.entryList().at(i)+"/",tk-1,f,t);
        }
        else if (!l.at(i).isHidden()) qWarning()<<"Sconosciuto";

    }
}

//ACCES FUNCTIONS
QList<tag> tags(QSqlQuery &tq,QSqlQuery &rq){
    QList<tag> t;
    tag temp;

    QString t1,t2;
    int id;
    int pId;

    if (tq.exec("SELECT tag.name,tag.key,tag.parent FROM tag;")){
        while (tq.next()){
            t1=tq.value(0).toString();
            id=tq.value(1).toInt();
            pId=tq.value(2).toInt();

            if (rq.exec("SELECT tag.name FROM tag WHERE tag.key="+QString::number(pId)+");")) {
                t2=rq.value(0).toString();
            }

            temp.name=t1;
            temp.parent=t2;
            temp.id=id;

            t.push_back(temp);
        }

        qWarning()<<"NTAGS: "<<t.length();

        return t;
    }
    else qWarning()<<"Errore nella query 3";
    return t;
}

QList<file> files(QSqlQuery &fq){
    QList<file> t;
    file temp;
    if (fq.exec("SELECT file.name,file.path FROM file;")){
        while(fq.next()){
            temp.name=fq.value(0).toString();
            temp.path=fq.value(1).toString();
            t.push_back(temp);
            qWarning()<<"NAME: "<<temp.name;
        }
        qWarning()<<"NFILES: "<<t.length();
        return t;
    }
    else qWarning()<<"Errore nella query 4";
    return t;
}


int main(int argc, char *argv[])
{
    QString path;

    //Check for the config and db directory
    QDir dir;
    if (!dir.exists(QDir::homePath()+"/rationality/")) dir.mkdir(QDir::homePath()+"/rationality/");

    path=QDir::homePath()+"/rationality/";

    QCoreApplication a(argc, argv);
    qWarning()<<"Rationality daemon V 0.12";
    //Creation or opening of the db
    db = QSqlDatabase::addDatabase("QSQLITE","file.db");
    db.setDatabaseName(path+"file.db");

    if(!db.open())
           qWarning()<<"Connection error";
    else qWarning()<<"Connection done";

    QSqlQuery tableQuery(db);

    bool isNew=true;
    if (tableQuery.exec("CREATE TABLE tag (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,parent INTEGER NOT NULL, name TEXT NOT NULL, hidden INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
    else isNew=false;
    if (tableQuery.exec("CREATE TABLE filetag(file INTEGER NOT NULL, tag INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
    else isNew=false;
    if (tableQuery.exec("CREATE TABLE file (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL,  path TEXT NOT NULL, rating INTEGER );")) qWarning()<<"Tabella creata";
    else isNew=false;

    //FOR FUTURE
//    if (tableQuery.exec("CREATE TABLE person (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL, surname TEXT,  mail TEXT NOT NULL);")) qWarning()<<"Tabella creata";
//    else isNew=false;

    //Indexes of last tag and file
    int tgKey=-1;
    int flKey=-1;

    //Some sqlquery
    QSqlQuery tagQuery(db);
    QSqlQuery fileQuery(db);
    QSqlQuery relationQuery(db);

    //Initialization of db or of the key
    if (isNew){
        tagQuery.exec("INSERT INTO tag VALUES(-1,-3,'Root' );");
        tagQuery.exec("INSERT INTO tag VALUES(-2,-3,'Virtual');");
    }
    else {
        if (fileQuery.exec("SELECT MAX(file.key) FROM file;")) {
            if (fileQuery.next())
                flKey=fileQuery.value(0).toInt();
        }
        else qWarning()<<"Query 1 sbagliata";
        if (tagQuery.exec("SELECT MAX(tag.key) FROM tag;")){
            if (tagQuery.next())
                tgKey=tagQuery.value(0).toInt();
        }
        else qWarning()<<"Query 2 sbagliata";
    }
    flKey++;
    tgKey++;

    qWarning()<<"FileKey: "<<flKey;
    qWarning()<<"TagKey: "<<tgKey;
    QList<file> f=files(fileQuery);
    QList<tag> t=tags(tagQuery,fileQuery);

    scanFolder(relationQuery,tgKey,flKey,path,-1,f,t);

    db.close();
    return 0;

}
