#ifndef SAVER_H
#define SAVER_H

#include <QRunnable>
#include <QList>
#include <QJsonObject>

class Saver : public QRunnable
{
public:
    Saver(QString, int, QList <QJsonObject>);
    void run();
    QString path;
    int row;
    QList <QJsonObject> object;
};

#endif // SAVER_H
