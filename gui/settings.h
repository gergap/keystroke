#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QPoint>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int fontSize         READ fontSize     WRITE setFontSize     NOTIFY fontSizeChanged)
    Q_PROPERTY(int fadeoutTime      READ fadeoutTime  WRITE setFadeoutTime  NOTIFY fadeoutTimeChanged)
    Q_PROPERTY(int dockWidth        READ dockWidth    WRITE setDockWidth    NOTIFY dockWidthChanged)
    Q_PROPERTY(int dockHeight       READ dockHeight   WRITE setDockHeight   NOTIFY dockHeightChanged)
    Q_PROPERTY(QPoint dockPosition  READ dockPosition WRITE setDockPosition NOTIFY dockPositionChanged)
    Settings(QObject *parent = 0);
public:
    virtual ~Settings();

    int fontSize() const;
    void setFontSize(int val);
    int fadeoutTime() const;
    void setFadeoutTime(int val);
    int dockWidth() const;
    void setDockWidth(int val);
    int dockHeight() const;
    void setDockHeight(int val);
    QPoint dockPosition() const;
    void setDockPosition(const QPoint &val);

    static Settings *instance();

signals:
    void fontSizeChanged(int newVal);
    void fadeoutTimeChanged(int newVal);
    void dockWidthChanged(int newVal);
    void dockHeightChanged(int newVal);
    void dockPositionChanged(const QPoint &newVal);

private:
    int m_fontSize;
    int m_fadeoutTime;
    int m_dockWidth;
    int m_dockHeight;
    QPoint m_dockPos;
    static Settings *m_instance;
};

#endif /* end of include guard: SETTINGS_H */

