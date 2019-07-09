#ifndef TRIMPIC_H
#define TRIMPIC_H

#include <QObject>
#include <QImage>

class TrimPic : public QObject
{
    Q_OBJECT
public:
    explicit TrimPic(QObject *parent = nullptr);
    QString Path;
    int LineWidth;
    int width;
    int height;
    int w;
    int h;
    int quality=80;
    int forceResize=0;

signals:
    void progress(int progress);
    void echoInfo(QString info);
    void unlockButton(bool T);
private:
    QImage resizeAndFullfill(QImage input,int w,int h);
public slots:
    void TrimPicture();
};

#endif // TRIMPIC_H
