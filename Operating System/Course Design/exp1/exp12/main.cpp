#include "mainwindow.h"
#include <QApplication>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>


int main(int argc, char *argv[])
{
    pid_t p1,p2,p3;
    while((p1=fork())==-1);
    if(p1!=0)
        while((p2=fork())==-1);
    if(p1!=0&&p2!=0)
        while((p3=fork())==-1);

    if(p1==0){
        QApplication a(argc, argv);
        MainWindow w(1);
        w.setWindowTitle("System Time");
        w.show();
        return a.exec();
    }
    else if(p2==0){
        QApplication b(argc, argv);
        MainWindow w(2);
        w.setWindowTitle("Loop Display");
        w.show();
        return b.exec();
    }
    else if(p3==0){
        QApplication c(argc, argv);
        MainWindow w(3);
        w.setWindowTitle("Cumulative Summation");
        w.show();
        return c.exec();
    }

    waitpid(p1,NULL,0);
    waitpid(p2,NULL,0);
    waitpid(p3,NULL,0);
    return 0;
}
