#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),SortUporDown(1),ColumnNum(0),ColumnCount(7),SearchInfo(false),cx(0),MAX(30)
{
    ui->setupUi(this);

    index = ui->tabWidget->currentIndex();
    QTimer *timer = new QTimer();
    this->SystemInfo();

    connect(timer,SIGNAL(timeout()),this,SLOT(TimeUpdate()));
    connect(timer,SIGNAL(timeout()),this,SLOT(MemInfo()));
    connect(timer,SIGNAL(timeout()),this,SLOT(DrawCurve()));
    QHeaderView *headerGoods = ui->ProcessInfo->horizontalHeader();
    connect(headerGoods, SIGNAL(sectionClicked(int)), this, SLOT (ChangeColumnNum(int)));
    connect(timer,SIGNAL(timeout()),this,SLOT(sortByColumn()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ProcessInfoUpdate()));

    
    this->ProcessInfo();
    this->ProcessInfo();
    timer->start(1000);

    ui->Update->setText("Update");

    //MemInfo
    ui->CPU_31->setText("CPU");
    ui->MEM->setText("内存信息");

    //Process
    QStringList header;
    header<<"进程号"<<"进程名"<<"状态"<<"父进程号"<<"优先级"<<"内存占用"<<"CPU占用";
    ui->ProcessInfo->setColumnCount(ColumnCount);//设置列数
    ui->ProcessInfo->setHorizontalHeaderLabels(header);
    ui->ProcessInfo->horizontalHeader()->resizeSection(0,50);
    ui->ProcessInfo->horizontalHeader()->resizeSection(1,150);
    ui->ProcessInfo->horizontalHeader()->resizeSection(2,100);
    ui->ProcessInfo->horizontalHeader()->resizeSection(3,60);
    ui->ProcessInfo->horizontalHeader()->resizeSection(4,50);
    ui->ProcessInfo->horizontalHeader()->resizeSection(5,80);
    ui->ProcessInfo->horizontalHeader()->resizeSection(6,80);

    ui->ProcessInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ProcessInfo->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式

    ui->Search->setText("Search");
    ui->Kill->setText("Kill");
    ui->detail->setText("使用到的路径：\n\t/proc/%s/stat\n\t/proc/%s/statm\n\t/proc/stat\n\t/proc/meminfo\n\t/proc/sys/kernel/hostname\n\t/proc/version\n\t/proc/cpuinfo\n\t/proc/uptime\n注意事项\n\t请在点击update按钮之后进行进程页面相关操作");
    QFont font ( "Microsoft YaHei", 20, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    ui->detail->setFont(font);


    my_chart = new QChart();
    my_view = new QChartView(my_chart);
    my_view->setRenderHint(QPainter::Antialiasing); //设置抗锯齿
    my_view->setRubberBand(QChartView::RectangleRubberBand);

    series_cpu = new QLineSeries;
    series_mem = new QLineSeries;
    series_swap = new QLineSeries;

    scatterseries_cpu = new QScatterSeries(this);
    scatterseries_cpu->setMarkerShape(QScatterSeries::MarkerShapeCircle);//设置点的类型
    scatterseries_cpu->setMarkerSize(10); //设置点的大小

    scatterseries_mem = new QScatterSeries(this);
    scatterseries_mem->setMarkerShape(QScatterSeries::MarkerShapeCircle);//设置点的类型
    scatterseries_mem->setMarkerSize(10); //设置点的大小

    scatterseries_swap = new QScatterSeries(this);
    scatterseries_swap->setMarkerShape(QScatterSeries::MarkerShapeCircle);//设置点的类型
    scatterseries_swap->setMarkerSize(10); //设置点的大小

    my_chart->addSeries(series_cpu);
    my_chart->addSeries(series_mem);
    my_chart->addSeries(series_swap);
    my_chart->addSeries(scatterseries_cpu);
    my_chart->addSeries(scatterseries_mem);
    my_chart->addSeries(scatterseries_swap);

    my_chart->createDefaultAxes();

    axis_X = new QValueAxis;
    axis_X->setRange(0,MAX);
    axis_X->setLabelFormat("%g");
    axis_X->setTitleText("时间/s");

    axis_Y = new QValueAxis;
    axis_Y->setRange(0,100);
    axis_Y->setTitleText("CPU/MEM/SWAP利用率/%");


    series_cpu->setName("CPU");
    series_mem->setName("MEM");
    series_swap->setName("SWAP");
    scatterseries_cpu->setName("CPU Series");
    scatterseries_mem->setName("MEM Series");
    scatterseries_swap->setName("SWAP Series");

    my_chart->setAxisX(axis_X,series_cpu);
    my_chart->setAxisY(axis_Y,series_cpu);
    my_chart->setAxisX(axis_X,series_mem);
    my_chart->setAxisY(axis_Y,series_mem);
    my_chart->setAxisX(axis_X,series_swap);
    my_chart->setAxisY(axis_Y,series_swap);
    my_chart->setAxisX(axis_X,scatterseries_cpu);
    my_chart->setAxisY(axis_Y,scatterseries_cpu);
    my_chart->setAxisX(axis_X,scatterseries_mem);
    my_chart->setAxisY(axis_Y,scatterseries_mem);
    my_chart->setAxisX(axis_X,scatterseries_swap);
    my_chart->setAxisY(axis_Y,scatterseries_swap);

    my_chart->setTitle(QString::number(MAX)+"s内CPU/MEM/SWAP使用率图像");
    ui->View->setChart(my_chart);

    QPen p_cpu,p_mem,p_swap;
    p_cpu.setWidth(3);
    p_cpu.setColor(Qt::black);
    p_mem.setWidth(3);
    p_mem.setColor(Qt::red);
    p_swap.setWidth(3);
    p_swap.setColor(Qt::blue);

    scatterseries_cpu->setPen(p_cpu);
    scatterseries_mem->setPen(p_mem);
    scatterseries_swap->setPen(p_swap);
    series_cpu->setPen(p_cpu);
    series_mem->setPen(p_mem);
    series_swap->setPen(p_swap);

    connect(scatterseries_cpu, &QScatterSeries::hovered, this, &MainWindow::slotPointHoverd);//用于鼠标移动到点上显示数值
    connect(scatterseries_mem, &QScatterSeries::hovered, this, &MainWindow::slotPointHoverd);
    connect(scatterseries_swap, &QScatterSeries::hovered, this, &MainWindow::slotPointHoverd);
}
void MainWindow::slotPointHoverd(const QPointF &point, bool state)
{
    if (state) {
        ui->Value->setText(QString::asprintf("%1.0f%", point.y()));
        QPoint curPos = mapFromGlobal(QCursor::pos());
        ui->Value->move(curPos.x() - ui->Value->width() /2 , curPos.y() - ui->Value->height() * 4);//移动数值
        QPalette palette;
        palette.setColor(QPalette::Background, QColor(230, 230, 250));
        palette.setColor(QPalette::WindowText,QColor(106, 90, 205));
        ui->Value->setAutoFillBackground(true);
        ui->Value->setPalette(palette);
        ui->Value->show();//显示出来
    }
    else
        ui->Value->hide();//进行隐藏
}
void MainWindow::DrawCurve(void)
{
    if(series_cpu->count() > MAX)
    {
        series_cpu->pointsVector().pop_front();
        series_mem->pointsVector().pop_front();
        series_swap->pointsVector().pop_front();
        my_chart->axisX()->setRange(cx-MAX,cx);
    }
    series_cpu->append(cx,CPU_Curve);
    series_mem->append(cx,MEM_Curve);
    series_swap->append(cx,SWAP_Curve);

    if(cx%5 == 0 && scatterseries_cpu->count()*5 > MAX)
    {
        scatterseries_cpu->pointsVector().pop_front();
        scatterseries_mem->pointsVector().pop_front();
        scatterseries_swap->pointsVector().pop_front();
    }
    if(cx%5 == 0)
    {
        scatterseries_cpu->append(cx,CPU_Curve);
        scatterseries_mem->append(cx,MEM_Curve);
        scatterseries_swap->append(cx,SWAP_Curve);
    }

    cx++;
}

void MainWindow::sortByColumn()
{
    if(SortUporDown)
    {
       ui->ProcessInfo->sortItems(ColumnNum, Qt::AscendingOrder);
    }
    else
    {
       ui->ProcessInfo->sortItems(ColumnNum, Qt::DescendingOrder);
    }
}

void MainWindow::ChangeColumnNum(int n)
{
    ColumnNum = n;
    if(SortUporDown)
       SortUporDown=false;
    else
       SortUporDown=true;
}

void MainWindow::ProcessInfo(void)
{
    QString text = ui->SearchInfo->text();
    int pid = 0,ppid = 0,priority = 0,Mem = 0,Cpu = 0;
    QString pname,status;
    DIR* dp;
    struct dirent* entry;
    struct stat statbuf;
    if((dp=opendir("/proc"))==nullptr)
        return;
    int n=0;
    chdir("/proc");
    while((entry=readdir(dp))!=nullptr)
    {
        if(lstat(entry->d_name,&statbuf)==-1)
        {
            printf("lstat error.\n");
            return;
        }

        if(S_ISDIR(statbuf.st_mode))
        {
            if((entry->d_name[0]=='.')||(entry->d_name[0]=='.'&&entry->d_name[1]=='.'))
                continue;

            int len = int(strlen(entry->d_name));
            int i , flag=0;
            for(i=0;i<len;++i)
            {
                if(entry->d_name[i]>'9' || entry->d_name[i]<'0')
                {
                    flag=1;
                    break;
                }
            }
            if(flag)continue;

            //stat
            QString path;path.sprintf("/proc/%s/stat",entry->d_name);
            QFile file1(path);
            file1.open(QIODevice::ReadOnly);
            QString temp = file1.readAll();
            QStringList list = temp.split(" ");
            pid = list[0].toInt();
            pname = list[1];pname.replace("(","");pname.replace(")","");
            status = list[2];
            ppid = list[3].toInt();
            priority = list[17].toInt();
            Cpu = list[13].toInt() + list[14].toInt() +list[15].toInt() +list[16].toInt();
            file1.close();

            //statm
            path.sprintf("/proc/%s/statm",entry->d_name);
            QFile file2(path);
            file2.open(QIODevice::ReadOnly);
            QString temp2= file2.readAll();
            QStringList list2 = temp2.split(" ");
            Mem = list2[0].toInt();

            file2.close();

            if(status=="R")
                status="Running";
            else if(status=="S")
                status="Sleeping";
            else if(status=="D")
                status="Disk sleep";
            else if(status=="Z")
                status="Zombie";
            else if(status=="T")
                status="Stopped";
            else if(status=="t")
                status="trace stopped";
            else if(status=="W")
                status="Paging";
            else if(status=="X" || status=="x")
                status="Dead";
            else if(status=="K")
                status="Wakekill";
            else if(status=="W")
                status="Waking";
            else if(status=="P")
                status="Parked";
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setData(Qt::DisplayRole, pid);
            ui->ProcessInfo->setItem(n,0,item);

            ui->ProcessInfo->setItem(n,1,new QTableWidgetItem(pname));
            ui->ProcessInfo->setItem(n,2,new QTableWidgetItem(status));

            QTableWidgetItem* item1 = new QTableWidgetItem();
            item1->setData(Qt::DisplayRole, ppid);
            ui->ProcessInfo->setItem(n,3,item1);

            QTableWidgetItem* item2 = new QTableWidgetItem();
            item2->setData(Qt::DisplayRole, priority);
            ui->ProcessInfo->setItem(n,4,item2);

            QTableWidgetItem* item3 = new QTableWidgetItem();
            item3->setData(Qt::DisplayRole, Mem);
            ui->ProcessInfo->setItem(n,5,item3);

            QTableWidgetItem* item4 = new QTableWidgetItem();
            item4->setData(Qt::DisplayRole, Cpu);
            ui->ProcessInfo->setItem(n,6,item4);

            if(SearchInfo)
            {
                if(text == "")
                {
                    ui->ProcessInfo->setRowHidden(n,false);
                }
                else
                {
                    ui->ProcessInfo->setRowHidden(n,true);
                }
            }
            n++;
        }

    }
    if(SearchInfo)
    {
        QList<QTableWidgetItem *> list = ui->ProcessInfo->findItems(text, Qt::MatchContains);
        if(!list.isEmpty())
        {
            for(int i = 0;i < list.count();i++)
            {
                ui->ProcessInfo->setRowHidden(list[i]->row(),false);
            }
        }
    }

    ProcessTotal = n;
    ui->total->setText("Total: " + QString::number(ProcessTotal));
    ui->ProcessInfo->setRowCount(n);//设置行数
    closedir(dp); 
}

void MainWindow::MemInfo(void)
{
    QString temp;
    QString text,text1;
    QStringList list;
    int pos,pos1;
    //主机名
    QFile file1("/proc/stat");file1.open(QIODevice::ReadOnly);
    int n = 0;
    temp = file1.readLine();
    temp.replace("  "," ");
    list = temp.split(" ");
    int a = 0;
    for(int i=0;i<list.size();i++)
        a +=list[i].toInt();
    int b = list[4].toInt();
    ui->CPU_32->setValue((a-b)*100/b);
    ui->ShowCPU->setText("CPU 利用率:"+ QString::number((a-b)*100/b) +"%");
    CPU_Curve = (a-b)*100/b;
    file1.close();


    int m = 0;
    QFile file2("/proc/meminfo");file2.open(QIODevice::ReadOnly);
    while(1)
    {
        temp = file2.readLine();
        if(temp == nullptr)
            break;
        if((pos = temp.indexOf("MemTotal")) != -1)
        {
            ui->MEM_1->setText(temp);
            pos1 = temp.indexOf("kB");
            a = temp.mid(pos+9,pos1-pos-9).toInt();
        }
        else if((pos = temp.indexOf("MemFree"))!=-1)
        {
            ui->MEM_2->setText(temp);
            pos1 = temp.indexOf("kB");
            b = temp.mid(pos+8,pos1-pos-8).toInt();
        }
        else if((pos = temp.indexOf("Cached")) != -1 && (pos = temp.indexOf("SwapCached")) == -1)
        {
            ui->MEM_3->setText(temp);
        }
        else if((pos = temp.indexOf("SwapCached"))!=-1)
        {
            ui->MEM_4->setText(temp);
        }
        else if((pos = temp.indexOf("SwapTotal"))!=-1)
        {
            ui->MEM_5->setText(temp);
            pos1 = temp.indexOf("kB");
            m = temp.mid(pos+10,pos1-pos-10).toInt();
        }
        else if((pos = temp.indexOf("SwapFree"))!=-1)
        {
            ui->MEM_6->setText(temp);
            pos1 = temp.indexOf("kB");
            n = temp.mid(pos+9,pos1-pos-9).toInt();
        }
    }
    ui->MEM_31->setValue((a-b)*100/a);
    ui->MEM_32->setValue((m-n)*100/m);
    ui->ShowMem->setText("MEM 利用率:"+ QString::number((a-b)*100/a) +"%");
    ui->ShowSwap->setText("SWAP 利用率:"+ QString::number((m-n)*100/m) +"%");
    MEM_Curve = (a-b)*100/a;
    SWAP_Curve = (m-n)*100/m;
    file2.close();
}

void MainWindow::SystemInfo(void)
{
    QString temp;
    QString text,text1;
    int pos,pos1,pos2;
    ui->OS->setText("操作系统信息");
    //主机名
    QFile file1("/proc/sys/kernel/hostname");file1.open(QIODevice::ReadOnly);
    temp = file1.readAll();
    ui->OS_1->setText("主机名\t\t:"+temp);
    file1.close();
    //ubuntu版本号  gcc版本号
    QFile file2("/proc/version");file2.open(QIODevice::ReadOnly);
    temp = file2.readAll();
    pos = temp.indexOf("(");
    ui->OS_2->setText("系统版本号\t:"+temp.mid(0,pos-1));
    pos1 = temp.indexOf("gcc");
    pos2 = temp.indexOf("(",pos+1);
    pos2 = temp.indexOf("(",pos2+1);
    ui->OS_3->setText("gcc版本号\t:"+temp.mid(pos1,pos2-1-pos1-8));
    file2.close();

    //CPU
    ui->CPU->setText("CPU信息");
    QFile file3("/proc/cpuinfo");file3.open(QIODevice::ReadOnly);
    while(1)
    {
        temp = file3.readLine();
        if(temp == nullptr)
            break;
        pos = temp.indexOf("vendor_id");
        if(pos!=-1)
        {
            ui->CPU_1->setText(temp.mid(pos,temp.length()-1));
        }
        else if((pos = temp.indexOf("model name"))!=-1)
        {
            ui->CPU_2->setText(temp.mid(pos,temp.length()-1));
        }
        else if((pos = temp.indexOf("cpu MHz"))!=-1)
        {
            ui->CPU_3->setText(temp.mid(pos,temp.length()-1)+" HZ");
        }
        else if((pos = temp.indexOf("cache size"))!=-1)
        {
            ui->CPU_4->setText(temp.mid(pos,temp.length()-1)+" KB");
        }
    }
    file3.close();
}

void MainWindow::TimeUpdate(void)
{
    QDateTime CurrentTime=QDateTime::currentDateTime();

    QString Timestr=CurrentTime.toString(" yyyy年-MM月-dd日 hh:mm:ss "); //设置显示的格式

    ui->ShowTime->setText(Timestr);


    //uptime
    QString temp;
    QString text,text1;
    int pos;
    QFile file4("/proc/uptime");file4.open(QIODevice::ReadOnly);
    temp = file4.readLine();
    pos = temp.indexOf(" ");
    text = temp.mid(0,pos-1);
    text1 = temp.mid(pos+1,temp.length()-1);
    uint runtime = uint(text.toDouble());
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    uint nowtime = time.toTime_t();   //将当前时间转为时间戳
    uint opentime = nowtime - runtime;

    QDateTime Time1 = QDateTime::fromTime_t(opentime);
    QString Timestr1=Time1.toString("系统启动时间\t: yyyy年-MM月-dd日 hh:mm:ss "); //设置显示的格式
    ui->OpenTime->setText(Timestr1);

    ui->RunTime->setText("系统运行时间\t:  "+ QString::number(runtime/3600) + ":" + QString::number(runtime/60) + ":" + QString::number(runtime%60) );
    file4.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Reboot_clicked()
{
    system("reboot");
}

void MainWindow::on_Halt_clicked()
{
    system("halt");
}

void MainWindow::on_Kill_clicked()
{
    int row = ui->ProcessInfo->currentRow();
    QTableWidgetItem *item =  ui->ProcessInfo->item(row,0);
    QString text = item->text();
    if(text == nullptr)
        return;
    int pid = text.toInt();
    QMessageBox message(QMessageBox::Warning,"警告",
         "确定杀死进程" + QString::number(pid) + "?",QMessageBox::No|QMessageBox::Yes,nullptr);
    message.setDefaultButton(QMessageBox::Yes);
    if (message.exec()==QMessageBox::Yes)
    {
        std::string kill="kill " + QString::number(pid).toStdString();
        int ret = system(kill.c_str());
        if(ret >= 256)
                    QMessageBox::about(this,"提示","权限不足。");
        else if(ret >= 0)
            QMessageBox::about(this,"提示","进程已结束。");
        else
            QMessageBox::about(this,"提示","进程无法杀死。");
    }
}

void MainWindow::on_Search_clicked()
{
    SearchInfo = true;
    this->ProcessInfo();
}

void MainWindow::on_Update_clicked()
{
    this->ProcessInfo();
}

void MainWindow::ProcessInfoUpdate()
{
    int row = ui->ProcessInfo->currentRow();
    if(row < 0)
    {
        ui->Pid->setText("NULL");
        ui->Pname->setText("NULL");
        ui->Pstatus->setText("NULL");
        return;
    }

    QTableWidgetItem *item =  ui->ProcessInfo->item(row,0);
    ui->Pid->setText(item->text());

    QTableWidgetItem *item1 =  ui->ProcessInfo->item(row,1);
    ui->Pname->setText(item1->text());

    QTableWidgetItem *item2 =  ui->ProcessInfo->item(row,2);
    ui->Pstatus->setText(item2->text());
}
