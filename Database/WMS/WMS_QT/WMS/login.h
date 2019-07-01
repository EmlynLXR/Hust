#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"
#include "control.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LoginIn_clicked();

    void finishedSlot(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* m_accessManager;
    Worker* WorkerPage;
    std::string WorkerID;
    std::string WorkerPWD;
    int WorkerType;
    bool login;
    void LoginInByPWD();
};

#endif // MAINWINDOW_H
