#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <QTimer>
#include <QLabel>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>
#include <QtCharts>
#include <QPalette>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public:
    int index;
    bool SortUporDown;
    int ColumnNum;
    int ColumnCount;
    int ProcessTotal;
    bool SearchInfo;
    int CPU_Curve;
    int MEM_Curve;
    int SWAP_Curve;
    int cx;
    int MAX;
    QChart *my_chart;
    QLineSeries *series_mem,*series_cpu,*series_swap;
    QChartView *my_view;
    QValueAxis *axis_X,*axis_Y;
    QScatterSeries *scatterseries_mem,*scatterseries_swap,*scatterseries_cpu;

public slots:
    void TimeUpdate();
    void SystemInfo();
    void ProcessInfo();
    void MemInfo();
    void DrawCurve();
    void sortByColumn();
    void ChangeColumnNum(int);
    void ProcessInfoUpdate();
    void slotPointHoverd(const QPointF &point, bool state);
private slots:
    void on_Reboot_clicked();
    void on_Halt_clicked();
    void on_Search_clicked();
    void on_Update_clicked();
    void on_Kill_clicked();
};

#endif // MAINWINDOW_H
