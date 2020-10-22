#ifndef TRIMPIC_H
#define TRIMPIC_H

#include <QObject>
#include <QImage>

class TrimPic : public QObject
{
    Q_OBJECT
public:
    explicit TrimPic(QObject *parent = nullptr);
    ~TrimPic();
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
    void quit();
private:
    static QImage resizeAndFullfill(QImage input, int w, int h, bool forceResize);
    static void MergeIMG(int index,QStringList name,int w,int h, int width, int height, int LineWidth,QString Path,int quality,bool forceResize);
public slots:
    void TrimPicture();
};

#endif // TRIMPIC_H
