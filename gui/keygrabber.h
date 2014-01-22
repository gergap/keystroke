#ifndef KEYGRABBER_H
#define KEYGRABBER_H

#include <QThread>

class KeyGrabber : public QThread
{
    Q_OBJECT
public:
    explicit KeyGrabber(QObject *parent = 0);

    virtual void run();
    void stop();

signals:
    void keyPressed(const QString &key);
    void keyPressed_Internal(const QString &key);

private:
    bool m_bShutdown;
};

#endif /* end of include guard: KEYGRABBER_H */

