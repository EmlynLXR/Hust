#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int arg,QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int count;
    int total;
public slots:
    void win1(void);
    void win2(void);
    void win3(void);
};

#endif // MAINWINDOW_H
