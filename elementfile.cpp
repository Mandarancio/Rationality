#include "elementfile.h"
#include <QFileInfo>

ElementFile::ElementFile()
{
    haveInfo=false;
}


void ElementFile::getInfo(){
    haveInfo=true;
    QFileInfo file(Path()+Name());
    size=file.size();
    owner=file.owner();
    lastDate=file.lastModified().date();
    creationDate=file.created().date();
}

QString ElementFile::getCDate(){
    if (!haveInfo) getInfo();
    return creationDate.toString("d MMMM yyyy");
}

QString ElementFile::getLDate(){
    if (!haveInfo) getInfo();
    return lastDate.toString("d MMMM yyyy");
}

QString ElementFile::getOwner(){
    if (!haveInfo) getInfo();
    return owner;
}

QString ElementFile::humanSize(){
    if (!haveInfo) getInfo();
    int t=size;
    int i=0;
    while (t<2048){
        t/=1024;
        i++;
    }
    switch(i){
    case 0:
        return QString::number(t)+" B";
    case 1:
        return QString::number(t)+" kB";
    case 2:
        return QString::number(t)+" mB";
    case 3:
        return QString::number(t)+" gB";
    case 4:
        return QString::number(t)+" pB";
    default:
        return QString::number(t);
    }

}
