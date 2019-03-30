#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
#include<QLabel>
#include<QDateTime>

MainWindow::MainWindow(int arg,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),count(0),total(0)
{
    QTimer *timer = new QTimer(this);
    ui->setupUi(this);
    QFont font ( "Microsoft YaHei", 25, 75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    ui->label->setFont(font);
    timer->start(1000);
    switch(arg)
    {
        case 1:
            connect(timer,SIGNAL(timeout()),this,SLOT(win1()));
            break;
        case 2:
            connect(timer,SIGNAL(timeout()),this,SLOT(win2()));
            break;
        case 3:
            connect(timer,SIGNAL(timeout()),this,SLOT(win3()));
            break;
        default:
            break;
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::win1(void)
{
    QDateTime CurrentTime=QDateTime::currentDateTime();

    QString Timestr=CurrentTime.toString(" yyyy年-MM月-dd日 hh:mm:ss "); //设置显示的格式

    ui->label->setText(Timestr);
}
void MainWindow::win2(void)
{
    count = (count + 1)%10;

    ui->label->setText(QString::number(count));
}
void MainWindow::win3(void)
{
    count++;
    if(count <= 1000)
    {
        int pre = total;
        total += count;
        ui->label->setText(QString::number(pre)+"+"+QString::number(count)+"="+QString::number(total));
    }
}
