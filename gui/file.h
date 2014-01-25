#ifndef _FILE_H_
#define _FILE_H_

#include <QObject>

/** This class provides some file functions to QML. */
class File : public QObject
{
    Q_OBJECT
public:
    File(QObject *parent = 0);

    Q_INVOKABLE bool exists(const QString &filename);
};

#endif /* end of include guard: _FILE_H_ */

