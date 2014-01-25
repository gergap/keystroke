#include "file.h"
#include <QFile>

File::File(QObject *parent)
: QObject(parent)
{
}

bool File::exists(const QString &filename)
{
    QString f = filename;
    if (f.startsWith("qrc:"))
        f.remove(0, 3);
    QFile file(f);
    return file.exists();
}


