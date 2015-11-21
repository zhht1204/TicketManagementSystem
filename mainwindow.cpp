#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->classNum = 0;
    ui->runsInformationTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//按起终点站查询
int MainWindow::searchByStation(QString startStation,QString endStation)
{
    int i, j = 0;
    CLASS result[1000];
    for(i=0; i<classNum; i++)
    {
        if(QString::compare(startStation,records[i].startStation) == 0 &&
           QString::compare(endStation, records[i].endStation) == 0)
        {
            result[j++] = records[i];
        }
    }

    ui->searchRunsInformationTable->setRowCount(j);
    QString time, tripTime, capacity, ticketSold;
    for(i=0; i<j; i++)
    {
        time = result[i].hour + QString(":") + result[i].min;
        tripTime.setNum(result[i].tripTime);
        capacity = QString::number(result[i].capacity, 10);
        ticketSold = QString::number(result[i].ticketSold, 10);
        ui->searchRunsInformationTable->setItem(i, 0, new QTableWidgetItem(result[i].runs));
        ui->searchRunsInformationTable->setItem(i, 1, new QTableWidgetItem(time));
        ui->searchRunsInformationTable->setItem(i, 2, new QTableWidgetItem(result[i].startStation));
        ui->searchRunsInformationTable->setItem(i, 3, new QTableWidgetItem(result[i].endStation));
        ui->searchRunsInformationTable->setItem(i, 4, new QTableWidgetItem(tripTime));
        ui->searchRunsInformationTable->setItem(i, 5, new QTableWidgetItem(capacity));
        ui->searchRunsInformationTable->setItem(i, 6, new QTableWidgetItem(ticketSold));
    }
    ui->searchRunsInformationTable->show();
    ui->tabWidget->setCurrentIndex(2);

    return j;
}

//按班次查询函数
int MainWindow::searchByRuns(QString runsNumber)
{
    int i, j = 0;
    CLASS result[1000];
    for(i=0; i<classNum; i++)
    {
        if(QString::compare(runsNumber,records[i].runs) == 0)
        {
            result[j++] = records[i];
        }
    }

    ui->searchRunsInformationTable->setRowCount(j);
    QString time, tripTime, capacity, ticketSold;
    for(i=0; i<j; i++)
    {
        time = result[i].hour + QString(":") + result[i].min;
        tripTime.setNum(result[i].tripTime);
        capacity = QString::number(result[i].capacity, 10);
        ticketSold = QString::number(result[i].ticketSold, 10);
        ui->searchRunsInformationTable->setItem(i, 0, new QTableWidgetItem(result[i].runs));
        ui->searchRunsInformationTable->setItem(i, 1, new QTableWidgetItem(time));
        ui->searchRunsInformationTable->setItem(i, 2, new QTableWidgetItem(result[i].startStation));
        ui->searchRunsInformationTable->setItem(i, 3, new QTableWidgetItem(result[i].endStation));
        ui->searchRunsInformationTable->setItem(i, 4, new QTableWidgetItem(tripTime));
        ui->searchRunsInformationTable->setItem(i, 5, new QTableWidgetItem(capacity));
        ui->searchRunsInformationTable->setItem(i, 6, new QTableWidgetItem(ticketSold));
    }
    ui->searchRunsInformationTable->show();
    ui->tabWidget->setCurrentIndex(2);

    return j;
}

//售票
void MainWindow::ticketOrder()
{
    int rowNumber;
    if(ui->tabWidget->currentIndex() == 0)
    {
        rowNumber = ui->runsInformationTable->currentRow();
    }
    else if(ui->tabWidget->currentIndex() == 2)
    {
        rowNumber = ui->searchRunsInformationTable->currentRow();
        QString runs = ui->searchRunsInformationTable->itemAt(0, rowNumber)->text();
        int i;
        for(i=0; i<classNum; i++)
        {
            if(QString::compare(runs, this->records[i].runs) == 0)
            {
                rowNumber = i;
                ui->tabWidget->setCurrentIndex(0);
                ui->runsInformationTable->setCurrentCell(rowNumber, 0);
                break;
            }
        }
    }
    else
    {
         QMessageBox::about(this, "错误", "请切换页面");
         return;
    }
    if(rowNumber >= 0)
    {
        /*
        if(MainWindow::outOfTime(rowNumber) == 0)
        {
            QMessageBox::about(this, "售票失败", "该班次已过期");
        }*/
        if(this->records[rowNumber].ticketSold >= this->records[rowNumber].capacity)
        {
            QMessageBox::about(this, "售票失败", "车票已售完");
        }
        else
        {
            this->records[rowNumber].ticketSold++;
            MainWindow::showRuns();
        }
    }
    else
    {
        QMessageBox::about(this, "错误", "请选择班次");
    }
}

//退票
void MainWindow::ticketDelete()
{
    int rowNumber;
    if(ui->tabWidget->currentIndex() == 0)
    {
        rowNumber = ui->runsInformationTable->currentRow();
    }
    else if(ui->tabWidget->currentIndex() == 2)
    {
        rowNumber = ui->searchRunsInformationTable->currentRow();
        QString runs = ui->searchRunsInformationTable->itemAt(0, rowNumber)->text();
        int i;
        for(i=0; i<classNum; i++)
        {
            if(QString::compare(runs, this->records[i].runs) == 0)
            {
                rowNumber = i;
                ui->tabWidget->setCurrentIndex(0);
                ui->runsInformationTable->setCurrentCell(rowNumber, 0);
                break;
            }
        }
    }
    else
    {
         QMessageBox::about(this, "错误", "请切换页面");
         return;
    }
    if(rowNumber >= 0)
    {
        /*
        if(MainWindow::outOfTime(rowNumber) == 0)
        {
            QMessageBox::about(this, "退票失败", "该班次已过期");
        }*/
        if(this->records[rowNumber].ticketSold <= 0)
        {
            QMessageBox::about(this, "退票失败", "未有人购票");
        }
        else
        {
            this->records[rowNumber].ticketSold--;
            MainWindow::showRuns();
        }
    }
    else
    {
        QMessageBox::about(this, "错误", "请选择班次");
    }
}

//修改班次
void MainWindow::alterRuns()
{
    AlterRunsWindow *w = new AlterRunsWindow(this);
    connect(this, SIGNAL(sendInformation(int, QString,QString,QString,QString,QString,QString,QString)),
            w, SLOT(getInformation(int, QString,QString,QString,QString,QString,QString,QString)));
    connect(w, SIGNAL(sendInformation(int, QString,QString,QString,QString,QString,QString,QString)),
            this, SLOT(getInformation(int, QString,QString,QString,QString,QString,QString,QString)));
    int index = ui->runsInformationTable->currentRow();
    QString time = this->records[index].hour + QString(":") + this->records[index].min;
    QString tripTime;
    tripTime.setNum(records[index].tripTime);
    QString capacity = QString::number(records[index].capacity, 10);
    QString ticketSold = QString::number(records[index].ticketSold, 10);
    emit sendInformation(index, this->records[index].runs, time, this->records[index].startStation,
                         this->records[index].endStation, tripTime, capacity, ticketSold);
    w->exec();
}

//solt - sendInformation(~) from AlterRunsWindow
void MainWindow::getInformation(int index, QString runs, QString departTime,
                                QString startStation, QString endStation, QString tripTime,
                                QString capacity, QString ticketSold)
{
    this->records[index].runs = runs;
    QStringList timeArray = departTime.split(":");
    this->records[index].hour = timeArray.at(0);
    this->records[index].min = timeArray.at(1);
    this->records[index].startStation = startStation;
    this->records[index].endStation = endStation;
    this->records[index].tripTime = tripTime.toFloat();
    this->records[index].capacity = capacity.toInt();
    this->records[index].ticketSold = ticketSold.toInt();
    MainWindow::showRuns();
}

//判断时间是否超出函数
//i : 班次序号
int MainWindow::outOfTime(int i)
{
    struct tm *local;         //时间结构体
    time_t t;                 //把当前时间给t
    t=time(NULL);             //NULL在stdio.h中定义为0
    local=localtime(&t);      //获取当前系统时间
    if(local->tm_hour <= records[i].hour.toDouble() &&
       local->tm_min < records[i].min.toDouble())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}

//在主界面上显示班次
void MainWindow::showRuns()
{
    /*
    this->records[0].num = "10001";
    this->records[0].hour = "3";
    this->records[0].min = "24";
    this->records[0].from = "上海";
    this->records[0].to = "成都";
    this->records[0].hours = 25.9;
    this->records[0].max = 44;
    this->records[0].now =  9;
    this->classNum = 1;
    */
    int i;
    ui->runsInformationTable->setRowCount(this->classNum);
    QString time, tripTime, capacity, ticketSold;
    for(i=0; i<this->classNum; i++)
    {
        time = records[i].hour + QString(":") + records[i].min;
        tripTime.setNum(records[i].tripTime);
        capacity = QString::number(records[i].capacity, 10);
        ticketSold = QString::number(records[i].ticketSold, 10);
        ui->runsInformationTable->setItem(i, 0, new QTableWidgetItem(records[i].runs));
        ui->runsInformationTable->setItem(i, 1, new QTableWidgetItem(time));
        ui->runsInformationTable->setItem(i, 2, new QTableWidgetItem(records[i].startStation));
        ui->runsInformationTable->setItem(i, 3, new QTableWidgetItem(records[i].endStation));
        ui->runsInformationTable->setItem(i, 4, new QTableWidgetItem(tripTime));
        ui->runsInformationTable->setItem(i, 5, new QTableWidgetItem(capacity));
        ui->runsInformationTable->setItem(i, 6, new QTableWidgetItem(ticketSold));
    }
    ui->runsInformationTable->show();
    ui->tabWidget->setCurrentIndex(0);
}

//增加班次
void MainWindow::addRuns()
{
    AddRunsWindow* addWindow = new AddRunsWindow(this);
    connect(addWindow, SIGNAL(sendInformation(QString,QString,QString,QString,QString,QString,QString)), this, SLOT(getInformation(QString,QString,QString,QString,QString,QString,QString)));
    if(addWindow->exec() == QDialog::Accepted)
    {
        showRuns();
    }
}

//slot - sendInformation from AddRunsWindow
void MainWindow::getInformation(QString runs, QString departTime, QString startStation,
                                QString endStation, QString tripTime, QString capacity,
                                QString ticketSold)
{
    int i;
    bool flag = true;
    for(i=0; i<classNum; i++)
    {
        if(QString::compare(this->records[i].runs, runs) == 0)
        {
            flag = false;
        }
    }
    if(flag)
    {
        this->records[classNum].runs = runs;
        QStringList departTimeList;
        departTimeList = departTime.split(":");
        this->records[classNum].hour = departTimeList.at(0);
        this->records[classNum].min = departTimeList.at(1);
        this->records[classNum].startStation = startStation;
        this->records[classNum].endStation = endStation;
        this->records[classNum].tripTime = tripTime.toFloat();
        this->records[classNum].capacity = capacity.toInt();
        this->records[classNum].ticketSold = ticketSold.toInt();
        this->classNum++;
        MainWindow::showRuns();
    }
    else
    {
        QMessageBox::about(this, "添加无效", "班次已存在");
    }
}

//保存班次到文件
void MainWindow::saveRuns()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Save To"));
    fileDialog->setNameFilter(QString("Data file(*.dat)"));
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString path = fileDialog->selectedFiles()[0];
        //检查后缀
        if(!path.endsWith(QString(".dat"), Qt::CaseInsensitive))
        {
            path = path.append(QString(".dat"));
        }
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::warning(this, "请检查", "文件打开错误");
        }
        else
        {
            QDataStream out(&file);
            out << classNum;
            QChar tab('\t');
            int i;
            for(i=0; i<classNum; i++)
            {
                out << records[i].runs << tab;
                out << records[i].hour << tab;
                out << records[i].min << tab;
                out << records[i].startStation << tab;
                out << records[i].endStation << tab;
                out << records[i].tripTime << tab;
                out << records[i].capacity << tab;
                out << records[i].ticketSold << tab;
            }
            file.close();
        }
    }
    else
    {
        QMessageBox::information(NULL, tr("Path"), tr("你没有选择任何位置"));
    }

}

//从文件读取班次
void MainWindow::readRuns()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Load From"));
    fileDialog->setNameFilter(QString("Data file(*.dat)"));
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString path = fileDialog->selectedFiles()[0];
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this, "请检查", "文件打开错误");
        }
        else
        {
            QDataStream in(&file);
            in >> classNum;
            QChar tab('\t');
            int i;
            for(i=0; i<classNum; i++)
            {
                in >> records[i].runs >> tab;
                in >> records[i].hour >> tab;
                in >> records[i].min >> tab;
                in >> records[i].startStation >> tab;
                in >> records[i].endStation >> tab;
                in >> records[i].tripTime >> tab;
                in >> records[i].capacity >> tab;
                in >> records[i].ticketSold >> tab;
            }
            file.close();
            MainWindow::showRuns();
        }
    }
    else
    {
        QMessageBox::information(NULL, tr("Path"), tr("你没有选择任何位置"));
    }
}

//删除班次
void MainWindow::deleteRuns()
{
    if(ui->tabWidget->currentIndex() != 0)
    {
        QMessageBox::about(this, "错误", "请到主页面进行删除");
    }
    else
    {
        int rowNumber = ui->runsInformationTable->currentRow();
        if(rowNumber >= 0)
        {
            int i;
            for(i=rowNumber; i<classNum-1; i++)
            {
                this->records[i] = this->records[i + 1];
            }
            this->classNum--;
            MainWindow::showRuns();
        }
        else
        {
            QMessageBox::about(this, "错误", "未选择行");
        }
    }
}

void MainWindow::on_actionAddRuns_triggered()
{
    MainWindow::addRuns();
}

void MainWindow::on_actionSave_triggered()
{
    MainWindow::saveRuns();
}

void MainWindow::on_actionLoad_triggered()
{
    MainWindow::readRuns();
}

void MainWindow::on_actionDeleteRuns_triggered()
{
    if(ui->tabWidget->currentIndex() != 0)
    {
        QMessageBox::about(this, "错误", "请到主页面进行删除");
    }
    else
    {
        MainWindow::deleteRuns();
    }
}

void MainWindow::on_searchButton_clicked()
{
    if(ui->byRunsRadioButton->isChecked())
    {
        QString runsNumber = ui->runsNumberLineEdit->text();
        if(runsNumber.isEmpty())
        {
            QMessageBox::about(this, "错误", "请输入班次号");
        }
        else
        {
            MainWindow::searchByRuns(runsNumber);
        }
    }
    else if(ui->byStationRadioButton->isChecked())
    {
        QString startStation = ui->startStationLineEdit->text();
        QString endStation = ui->endStationLineEdit->text();
        if(startStation.isEmpty() || endStation.isEmpty())
        {
            QMessageBox::about(this, "错误", "请填写起终点站");
        }
        else
        {
            MainWindow::searchByStation(startStation, endStation);
        }
    }
    else
    {
        QMessageBox::about(this, "未选择", "请至少选择一种查询方式");
    }
}

void MainWindow::on_actionAlter_triggered()
{
    if(ui->tabWidget->currentIndex() != 0)
    {
        QMessageBox::about(this, "错误", "请到主页面进行修改");
    }
    else
    {
        MainWindow::alterRuns();
    }
}

void MainWindow::on_buyButton_clicked()
{
    MainWindow::ticketOrder();
}

void MainWindow::on_refundButton_clicked()
{
    MainWindow::ticketDelete();
}

void MainWindow::on_searchBuyButton_clicked()
{
    MainWindow::ticketOrder();
}

void MainWindow::on_searchRefundButton_clicked()
{
    MainWindow::ticketDelete();
}
