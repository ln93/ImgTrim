#include "trimpic.h"
#include <QPainter>
#include <QDir>
#include "omp.h"
TrimPic::TrimPic(QObject *parent) : QObject(parent)
{

}
QImage TrimPic::resizeAndFullfill(QImage input,int w,int h)
{
    QImage result=QImage(w,h,QImage::Format_RGB888);
    QPainter Painter(&result);
    Painter.fillRect(0,0,w,h,Qt::white);
    if(  ((w>=h)&&(input.width()<input.height()))  ||   ((w<h)&&(input.width()>=input.height())) )
    {
        QTransform rot;
        rot.rotate(90);
        input=input.transformed(rot);
    }
    if(forceResize)
    {
        input=input.scaled(w,h);
        QPointF point;
        point.setX(0);
        point.setY(0);
        Painter.drawImage(point,input);
        return(result);
    }
    double ratio=(double)w/input.width();
    QPointF point;
    point.setX(0);
    point.setY(((double)h-ratio*input.height())/2);

    if(((double)h-ratio*input.height())<0)
    {
        ratio=(double)h/input.height();
        point.setX(((double)w-ratio*input.width())/2);
        point.setY(0);

    }
    input=input.scaled(ratio*input.width(),ratio*input.height());
    Painter.drawImage(point,input);
    return (result);
}

void TrimPic::TrimPicture()
{
    //init path
    QDir dir(Path);
    dir.mkdir("result");
    //init pic size
    int index=0;
    //get File Name
    QStringList name,filters;
    filters<< "*.jpg" <<"*.png" << "*.bmp";
    name=dir.entryList(filters,QDir::Files|QDir::Readable,QDir::Name);

    //batch progress
    int showindex=0;
    int resultmaxIndex=name.count()/(w*h);
    if(name.count()%(w*h)>0)
        resultmaxIndex++;
#pragma omp parallel for
    for(index=0;index<resultmaxIndex;index++)
    {
        //prepare a white pic
        QImage result=QImage(width,height,QImage::Format_RGB888);
        QPainter Painter(&result);
        Painter.fillRect(0,0,width,height,Qt::white);

        for(int i=0;i<w;i++)
            for(int j=0;j<h;j++)
            {
                QPointF point;
                point.setX(i*width/w+LineWidth);
                point.setY(j*height/h+LineWidth);
                if(index*w*h+i*h+j>=name.count())
                    break;
                QImage img1(Path+"\\"+name[index*w*h+i*h+j]);
                img1=resizeAndFullfill(img1,width/w-2*LineWidth,height/h-2*LineWidth);
                Painter.drawImage(point,img1);
                //save img
            }

        result.save(Path+"//result//"+QString::number(index)+".jpg","JPG",quality);
#pragma omp critical
        {
            emit progress(showindex*w*h*100/name.count());
            showindex++;
        }
    }
    emit progress(100);

}
