#include "element.h"

Element::Element(QObject *parent) :
    QObject(parent)
{
    key=-3;
    isRelation=false;
}

void Element::setName(QString name){
    this->name=name;
//    if (!isRelation){
//        type=mime.fromFileName(name);
//        if (type.length()==0) {
//            type="Unknow";
//            description="Unknow";
//        }
//        else description=mime.description();
//    }
}

void Element::setKey(int k){
    if (k > -3) key=k;
}

void Element::setType(QString t){
    if (t.length())
        type=t;
    else type="Unknow";
}

void Element::setDescription(QString d){
    if (d.length())
        description=d;
    else description="Unknow";
}

void Element::setRelation(bool r){
    isRelation=r;
}

void Element::addTag(QString tag){
    tags.push_back(tag);
}

void Element::clearTags(){
    tags.clear();
}

void Element::setPath(QString p){
    path=p;
}


int Element::Key(){
    return key;
}
bool Element::isARelation(){
    return isRelation;
}

QString Element::Name(){
    return name;
}

QString Element::Type(){
    return type;
}

QString Element::Path(){
    return path;
}

QString Element::Description(){
    return description;
}

QList<QString> Element::Tags(){
    return tags;
}

