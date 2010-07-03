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

struct tag{
    QString name;
    QString parent;
    int id;
};

struct file{
    QString name;
    QString path;
};



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

void addDate(QSqlQuery &tq, QSqlQuery rq,QList<tag> tags, QDateTime t, int key,int &tgkey){
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
        tq.exec("INSERT INTO tag VALUES("+QString::number(tgkey)+", '"+t1.name+"');");
        rq.exec("INSERT INTO parent VALUES("+QString::number(tgkey)+", -2);");

        p2=tgkey;
        tgkey++;
        t2.id=tgkey;
        tq.exec("INSERT INTO tag VALUES("+QString::number(tgkey)+", '"+t2.name+"');");
        rq.exec("INSERT INTO parent VALUES("+QString::number(tgkey)+", "+QString::number(p2)+");");

        p3=tgkey;
        tgkey++;
        t3.id=tgkey;
        tq.exec("INSERT INTO tag VALUES("+QString::number(tgkey)+", '"+t3.name+"');");
        rq.exec("INSERT INTO parent VALUES("+QString::number(tgkey)+", "+QString::number(p3)+");");
        tgkey++;


    }
    else {
        t1.id=containsTag(tags,t1);
        p2=t1.id;

        if (!containsTag(tags,t2)){

            t2.id=tgkey;
            tq.exec("INSERT INTO tag VALUES("+QString::number(tgkey)+", '"+t2.name+"');");
            rq.exec("INSERT INTO parent VALUES("+QString::number(tgkey)+", "+QString::number(p2)+");");

            p3=tgkey;
            tgkey++;
            t3.id=tgkey;
            tq.exec("INSERT INTO tag VALUES("+QString::number(tgkey)+", '"+t3.name+"');");
            rq.exec("INSERT INTO parent VALUES("+QString::number(tgkey)+", "+QString::number(p3)+");");
            tgkey++;
        }
        else {
            t2.id=containsTag(tags,t2);
            p3=t2.id;
            if (!containsTag(tags,t3)) {
                t3.id=tgkey;
                tq.exec("INSERT INTO tag VALUES("+QString::number(tgkey)+", '"+t3.name+"');");
                rq.exec("INSERT INTO parent VALUES("+QString::number(tgkey)+", "+QString::number(p3)+");");
                tgkey++;
            }
            else
                t3.id=containsTag(tags,t3);
        }
    }
    //ASSIGNATION OF THE TAGS TO THE FILE
    rq.exec("INSERT INTO filetag VALUES("+QString::number(key)+", "+QString::number(t1.id)+");");
    rq.exec("INSERT INTO filetag VALUES("+QString::number(key)+", "+QString::number(t2.id)+");");
    rq.exec("INSERT INTO filetag VALUES("+QString::number(key)+", "+QString::number(t3.id)+");");
}

//TO UNDERSTAND IF IS BETTER MEMORIZE THE LAST UPDATE TO FILE OR THE CREATION DATE

void scanFolder(QSqlQuery & fq,QSqlQuery & tq,QSqlQuery & rq, int &tk, int &fk, QString path,int pId, QList<file> f, QList<tag> t){

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
            if (!containsFile(f,file) && fq.exec("INSERT INTO file VALUES( "+QString::number(fk)+" , '"+dir.entryList().at(i)+"' , '"+path+"' , 0 );")) {
                if (!rq.exec("INSERT INTO filetag VALUES( "+QString::number(fk)+" , "+QString::number(pId)+" );")) qWarning()<<"Relazione non creata";
                else {
                    addDate(tq,rq,t,l.at(i).created(),fk,tk);
                    fk++;
                }
            }
        }
        else if (l.at(i).isDir() && !l.at(i).isHidden() && QString::compare(dir.entryList().at(i),".") && QString::compare(dir.entryList().at(i),"..")){
            tag.name=dir.entryList().at(i);

            if (!containsTag(t,tag) && tq.exec("INSERT INTO tag VALUES( "+QString::number(tk)+" , '"+dir.entryList().at(i)+"');")) {
                if (!rq.exec("INSERT INTO parent VALUES( "+QString::number(tk)+" , "+QString::number(pId)+" );")) qWarning()<<"Parentela non creata";
                tk++;

            }

            scanFolder(fq,tq,rq,tk,fk,path+dir.entryList().at(i)+"/",tk-1,f,t);
        }
        else if (!l.at(i).isHidden()) qWarning()<<"Sconosciuto";

    }
}

QList<tag> tags(QSqlQuery &tq,QSqlQuery &rq){
    QList<tag> t;
    tag temp;

    QString t1,t2;
    int id;

    if (tq.exec("SELECT tag.name,tag.key FROM tag;")){
        while (tq.next()){
            t1=tq.value(0).toString();
            id=tq.value(1).toInt();

            if (rq.exec("SELECT tag.name FROM tag JOIN parent ON tag.key=parent.parent WHERE parent.child="+QString::number(id)+");")) {
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
    //path=QDir::homePath();
    path=QDir::homePath()+"/rationality/";

    QCoreApplication a(argc, argv);
    qWarning()<<"Rationality daemon V 0.12";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","file.db");
    db.setDatabaseName(QDir::homePath()+"/.rationality/file.db");
    if(!db.open())
           qWarning()<<"Errore di connessione";
    else qWarning()<<"Connessione effettuata";
    QSqlQuery tableQuery(db);

    bool isNew=true;
    if (tableQuery.exec("CREATE TABLE tag (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL);")) qWarning()<<"Tabella creata";
    else isNew=false;
    if (tableQuery.exec("CREATE TABLE parent (child INTEGER NOT NULL, parent INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
    else isNew=false;
    if (tableQuery.exec("CREATE TABLE filetag(file INTEGER NOT NULL, tag INTEGER NOT NULL);")) qWarning()<<"Tabella creata";
    else isNew=false;
    if (tableQuery.exec("CREATE TABLE file (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL,  path TEXT NOT NULL, rating INTEGER );")) qWarning()<<"Tabella creata";
    else isNew=false;
//    if (tableQuery.exec("CREATE TABLE person (key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL, surname TEXT,  mail TEXT NOT NULL);")) qWarning()<<"Tabella creata";
//    else isNew=false;

    int tgKey=-1;
    int flKey=-1;

    QSqlQuery tagQuery(db);
    QSqlQuery fileQuery(db);
    QSqlQuery relationQuery(db);

    if (isNew){
        tagQuery.exec("INSERT INTO tag VALUES(-1,'Root' );");
        tagQuery.exec("INSERT INTO tag VALUES(-2,'Virtual');");
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

    scanFolder(fileQuery,tagQuery,relationQuery,tgKey,flKey,path,-1,f,t);

    db.close();
    return 0;

}
