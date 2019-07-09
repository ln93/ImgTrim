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
    ui->startTrimPushButton->setEnabled(false);
    QFileDialog *QF=new QFileDialog(this);
    QF->setFileMode(QFileDialog::Directory);
    QF->setWindowTitle(QString("打开含有图片的文件夹"));
    QF->setDirectory(QString("./"));
    QString Path;
    if(QF->exec())
    {
        QStringList FP;
        FP=QF->selectedFiles();
        if(!FP.isEmpty())
        {
            Path=FP[0];
        }
        else
        {
            return;
        }
    }
    if(Path=="")//fix linux related issues
        return;
    TrimPic *Trim=new TrimPic;
    //init
    Trim->h=ui->FrameHLineEdit->text().toInt();
    Trim->w=ui->FrameWLineEdit->text().toInt();
    Trim->Path=Path;
    Trim->width=ui->WidthLineEdit->text().toInt();
    Trim->height=ui->HeightLineEdit->text().toInt();
    Trim->LineWidth=ui->whiteLineWidthLineEdit->text().toInt();
    Trim->quality=ui->imgQualityHorizontalSlider->value();
    Trim->forceResize=ui->ForceResizeCheckBox->isChecked();
    QThread *Thread=new QThread;
    Trim->moveToThread(Thread);
    connect(Thread,SIGNAL(started()),Trim,SLOT(TrimPicture()));
    connect(Trim,SIGNAL(progress(int)),ui->progressBar,SLOT(setValue(int)));
    connect(Thread,SIGNAL(finished()),Trim,SLOT(deleteLater()));
    connect(Thread,SIGNAL(finished()),Thread,SLOT(deleteLater()));
    connect(Trim,SIGNAL(unlockbutton(bool)),ui->startTrimPushButton,SLOT(setEnabled(bool)));
    connect(Trim,SIGNAL(echoInfo(QString)),ui->infoLabel,SLOT(setText(QString)));
    Thread->start();
}

void MainWindow::on_PrintPreferenceComboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:ui->HeightLineEdit->setText("1400");
        ui->WidthLineEdit->setText("2000");
        break;
    case 1:ui->HeightLineEdit->setText("200");
        ui->WidthLineEdit->setText("3000");
        break;
    case 2:ui->HeightLineEdit->setText("2500");
        ui->WidthLineEdit->setText("3500");
        break;
    case 3:ui->HeightLineEdit->setText("3000");
        ui->WidthLineEdit->setText("4000");
        break;
    case 4:ui->HeightLineEdit->setText("4000");
        ui->WidthLineEdit->setText("6000");
        break;
    case 5:ui->HeightLineEdit->setText("5000");
        ui->WidthLineEdit->setText("6000");
        break;
    }
}
