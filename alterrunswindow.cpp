#include "alterrunswindow.h"
#include "ui_alterrunswindow.h"

AlterRunsWindow::AlterRunsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlterRunsWindow)
{
    ui->setupUi(this);
}

AlterRunsWindow::~AlterRunsWindow()
{
    delete ui;
}

void AlterRunsWindow::on_buttonBox_accepted()
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
        if(floatRegex.exactMatch(tripTime) && timeRegex.exactMatch(time) &&
           intRegex.exactMatch(capacity) && intRegex.exactMatch(ticketSold))
        {
            emit sendInformation(this->index, runs, time, startStation, endStation, tripTime, capacity, ticketSold);
            hide();
        }
        else
        {
            QMessageBox::warning(this, "格式错误", "请检查各值格式");
        }
    }
}

void AlterRunsWindow::getInformation(int index, QString runs, QString departTime,
                                     QString startStation, QString endStation, QString tripTime,
                                     QString capacity, QString ticketSold)
{
    this->index = index;
    ui->runsLineEdit->setText(runs);
    ui->departTimeLineEdit->setText(departTime);
    ui->startStationLineEdit->setText(startStation);
    ui->endStationLineEdit->setText(endStation);
    ui->tripTimeLineEdit->setText(tripTime);
    ui->capacityLineEdit->setText(capacity);
    ui->ticketSoldLineEdit->setText(ticketSold);
}
