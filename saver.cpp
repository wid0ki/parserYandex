#include "saver.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Saver::Saver(QString path, int row, QList <QJsonObject> object)
{
    this->row = row;
    this->object = object;
    this->path = path + object.at(row).value("url").toString().replace("http://","").replace("/","")+".txt";
}

void Saver::run()
{
    QFile fileOut(path);
    QTextStream os(&fileOut);
    if (!fileOut.open(QIODevice::WriteOnly)) {
        qDebug()<<"Can't open file for writing path: "<<path;
    }
    os.setCodec("UTF-8");
    os<<"url: "<<object.at(row).value("url").toString()<<"; title: "<<object.at(row).value("title").toString()<<
        "; article: "<<object.at(row).value("article").toString()<<"; green_line: "<<object.at(row).value("green_line").toString();
    fileOut.close();
}
