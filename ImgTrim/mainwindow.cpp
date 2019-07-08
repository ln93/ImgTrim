#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trimpic.h"
#include <QFileDialog>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startTrimPushButton_clicked()
{
    QFileDialog *QF=new QFileDialog(this);
    QF->setFileMode(QFileDialog::Directory);
    QF->setWindowTitle(QString("打开含有图片的文件夹"));
    QF->setDirectory(QString("./"));
    QString Path;
    if(QF->exec())
    {
        QStringList FP=QF->selectedFiles();
        if(!FP.isEmpty())
        {
            Path=FP[0];
        }
    }

    TrimPic *Trim=new TrimPic;
    //init
    Trim->h=ui->FrameHLineEdit->text().toInt();
    Trim->w=ui->FrameWLineEdit->text().toInt();
    Trim->Path=Path;
    Trim->width=ui->WidthLineEdit->text().toInt();
    Trim->height=ui->HeightLineEdit->text().toInt();
    Trim->LineWidth=ui->whiteLineWidthLineEdit->text().toInt();
    Trim->quality=ui->imgQualitySpinBox->text().toInt();
    Trim->forceResize=ui->ForceResizeCheckBox->isChecked();
    QThread *Thread=new QThread;
    Trim->moveToThread(Thread);
    connect(Thread,SIGNAL(started()),Trim,SLOT(TrimPicture()));
    connect(Trim,SIGNAL(progress(int)),ui->progressBar,SLOT(setValue(int)));
    connect(Thread,SIGNAL(finished()),Trim,SLOT(deleteLater()));
    connect(Thread,SIGNAL(finished()),Thread,SLOT(deleteLater()));
    Thread->start();
}
