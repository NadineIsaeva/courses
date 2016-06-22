#ifndef MEMEITEM_H
#define MEMEITEM_H

#include <QString>
#include <QPushButton>

class MemeItem : public QObject
{
private:
public:
    MemeItem(QString path, int category);
    QString path;
    int category;
};

#endif // MEMEITEM_H
