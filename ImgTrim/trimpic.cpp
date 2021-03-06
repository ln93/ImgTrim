#include "trimpic.h"
#include <QPainter>
#include <QDir>
#include <thread>
TrimPic::TrimPic(QObject *parent) : QObject(parent)
{

}
TrimPic::~TrimPic()
{
    unlockButton(true);
}
QImage TrimPic::resizeAndFullfill(QImage input,int w,int h,bool forceResize)
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
void TrimPic::MergeIMG(int index,QStringList name,int w,int h, int width, int
height, int LineWidth,QString Path,int quality,bool forceResize)
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
            QImage img1(Path+"//"+name[index*w*h+i*h+j]);
            img1=resizeAndFullfill(img1,width/w-2*LineWidth,height/h-2*LineWidth,forceResize);
            Painter.drawImage(point,img1);
            //save img
        }

    result.save(Path+"//result//"+QString::number(index)+".jpg","JPG",quality);

}
void TrimPic::TrimPicture()
{
    //init path
    QDir dir(Path);
    //init pic size
    int index=0;
    //get File Name
    QStringList name,filters;
    filters<< "*.jpg" <<"*.png" << "*.bmp";
    name=dir.entryList(filters,QDir::Files|QDir::Readable,QDir::Name);
    //is the dir empty?
    if(name.count()==0)
    {
        echoInfo(QString("文件夹中不含有效图片。"));
        unlockButton(true);
        quit();
        return;
    }
    else
    {
        echoInfo(QString("图像合成中……"));
    }
    dir.mkdir("result");
    //batch progress
    int showindex=0;
    int resultmaxIndex=name.count()/(w*h);
    if(name.count()%(w*h)>0)
        resultmaxIndex++;
    std::thread worker[std::thread::hardware_concurrency()];
    for(index=0;index<resultmaxIndex;index+=std::thread::hardware_concurrency())
    {
            for(int i=0;i<std::thread::hardware_concurrency()&&i+index<resultmaxIndex;i++)
            {
                worker[i]=std::thread(MergeIMG,index+i,name,w,h,width,height,LineWidth,Path,quality,forceResize);

            }
            for(int i=0;i<std::thread::hardware_concurrency()&&i+index<resultmaxIndex;i++)
            {
                worker[i].join();
            }
            emit progress(showindex*w*h*100/name.count());
            showindex++;
    }
    emit progress(100);
    echoInfo(QString("图像已保存在")+Path+QString("/result文件夹下。\n")+QString("照片已拼接为")+QString::number(resultmaxIndex)+QString("张。\n使用了")+QString::number(std::thread::hardware_concurrency())+QString("个线程。"));
    unlockButton(true);
    quit();

}
