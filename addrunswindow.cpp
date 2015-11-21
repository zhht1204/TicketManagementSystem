#include "addrunswindow.h"
#include "ui_addrunswindow.h"

extern QString runs;

AddRunsWindow::AddRunsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRunsWindow)
{
    ui->setupUi(this);
}

AddRunsWindow::~AddRunsWindow()
{
    delete ui;
}

void AddRunsWindow::on_buttonBox_accepted()
{
    QString runs = ui->runsLineEdit->text();
    QString time = ui->departTimeLineEdit->text();
    QString startStation = ui->startStationLineEdit->text();
    QString endStation = ui->endStationLineEdit->text();
    QString tripTime = ui->tripTimeLineEdit->text();
    QString capacity = ui->capacityLineEdit->text();
    QString ticketSold = ui->ticketSoldLineEdit->text();
    if(runs.isEmpty() || time.isEmpty() || startStation.isEmpty() ||
            endStation.isEmpty() || tripTime.isEmpty() || capacity.isEmpty() ||
            ticketSold.isEmpty())
    {
        QMessageBox::warning(this, "错误", "请填完整");
    }
    else
    {
        QRegExp intRegex(QString("\\d+"));
        QRegExp floatRegex(QString("\\d*(\\.\\d*)?\\d$"));
        QRegExp timeRegex(QString("^(([0-1]?\\d)|(2[0-4])):(([0-5]?\\d)|60)$"));
        if(ticketSold.toInt() > capacity.toInt())
        {
            QMessageBox::warning(this, "数据错误", "售票数大于上限");
        }
        else if(floatRegex.exactMatch(tripTime) && timeRegex.exactMatch(time) &&
           intRegex.exactMatch(capacity) && intRegex.exactMatch(ticketSold))
        {
            emit sendInformation(runs, time, startStation, endStation, tripTime, capacity, ticketSold);
            hide();
        }
        else
        {
            QMessageBox::warning(this, "格式错误", "请检查各值格式");
        }
    }
}

void AddRunsWindow::on_buttonBox_rejected()
{
    hide();
}

