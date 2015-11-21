#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>            //宏定义函数
#include <string.h>           //串操作及内存操作函数
#include <stdlib.h>           //调用系统函数
#include <time.h>	          //时间库函数
#include <conio.h>            //输入输出函数
#include <QMessageBox>
#include <QFileDialog>
#include <QMainWindow>

#include "addrunswindow.h"
#include "alterrunswindow.h"

typedef struct TICKET            ////定义新结构体TICKET
{
    QString runs;           //车次编号
    QString hour;           //小时
    QString min;            //分钟
    QString startStation;          //起始站
    QString endStation;            //终点站
    float tripTime;            //车程实际时间
    int capacity;                //最大车载容量
    int ticketSold;                //已售票数
} CLASS;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int classNum;                        //班次总数
    CLASS records[1000];                 //多条记录
    void addRuns();                      //增加班次
    void deleteRuns();                   //删除班次
    void saveRuns();                     //保存到文件
    void readRuns();                     //从文件读取
    void alterRuns();                    //修改函数
    void quit();                         //退出函数
    void ticketOrder();                  //售票函数
    void ticketDelete();                 //删除函数
    int outOfTime(int);                          //判断时间是否超出函数
    int searchByStation(QString, QString);     //查询函数★//s1为起点站//s2为终点站
    int searchByRuns(QString);                 //班次查询函数
    void showRuns();                           //显示班次到界面

signals:
    void sendInformation(int, QString, QString, QString, QString, QString, QString, QString);

private slots:
    void on_actionQuit_triggered();

    void getInformation(QString, QString, QString, QString, QString, QString, QString);

    void getInformation(int , QString, QString, QString, QString, QString, QString, QString);

    void on_actionAddRuns_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionDeleteRuns_triggered();

    void on_searchButton_clicked();

    void on_actionAlter_triggered();

    void on_buyButton_clicked();

    void on_refundButton_clicked();

    void on_searchBuyButton_clicked();

    void on_searchRefundButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
